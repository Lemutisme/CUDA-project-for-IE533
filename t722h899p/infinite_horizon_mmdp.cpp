//
//  infinite_horizon_mmdp.cpp
//

#include "infinite_horizon_mmdp.h"

using namespace std;

// Default constructor sets number of states, actions, and models to 0.
InfiniteHorizonMMDP::InfiniteHorizonMMDP() : nstates(0), nactions(0), nmodels(0) {}

// Another construtor operator in case a test case InfiniteHorizonMMDP
// is needed instead of a random instance
InfiniteHorizonMMDP::InfiniteHorizonMMDP(const string  &total_filename, double discount_factor_in, double epsilon_in) {
    ifstream fin(total_filename); // Get total filename
    int nstates_in = 0, nactions_in = 0, nmodels_in = 0;
    string title = "";
    fin >> nstates_in >> nactions_in >> nmodels_in >> title;
    nstates = nstates_in;
    nactions = nactions_in;
    nmodels = nmodels_in;
    
    // Appropriately resizes each matrix and reads in the data from the file
    // All MMDP files must follow a specified format to be read-in consistently and correctly
    weights.resize(nmodels);
    double num = 0.0;
    epsilon = epsilon_in;
    discount_factor = discount_factor_in;
    convergence_threshold = epsilon * (1 - discount_factor) / (2 * discount_factor);

    double model_count = 0.0;
    for (int m = 0; m < nmodels; m++) {
        fin >> num;
        weights[m] = num;
        model_count += num;
    }
    if (model_count < 0.999)
        exit(1);

    fin >> title;
    initdist.resize(nmodels);
    for (int m = 0; m < nmodels; m++) {
        initdist[m].resize(nstates);
        double count = 0.0;
        for (int s = 0; s < nstates; s++) {
            fin >> num;
            initdist[m][s] = num;
            count += num;
        }

        if (count < 0.999)
            exit(1);
    }

    fin >> title;
    rewards.resize(nmodels);
    for (int m = 0; m < nmodels; m++) {
        rewards[m].resize(nstates);
        for (int s = 0; s < nstates; s++) {
            rewards[m][s].resize(nactions);
            for (int a = 0; a < nactions; a++) {
                fin >> num;
                rewards[m][s][a] = num;
            }
        }
    }

    fin >> title;
    tps.resize(nmodels);
    for (int m = 0; m < nmodels; m++) {
        tps[m].resize(nstates);
        for (int s = 0; s < nstates; s++) {
            tps[m][s].resize(nactions);
            for (int a = 0; a < nactions; a++) {
                tps[m][s][a].resize(nstates);
                double tp = 0;
                double count = 0.0;
                for (int i = 0; i < nstates; i++) {
                    fin >> num;
                    tp += num;
                    tps[m][s][a][i] = num;
                    count += num;
                }
                if (count < 0.999)
                    exit(1);

            }
        }
    }

    // Creates holder matrix for relaxation purposes
    completepols_holder.resize(nmodels);
    for (int m = 0; m < nmodels; m++) {
        completepols_holder[m].resize(nstates, -1);
    }

    vtgpol_holder.resize(nmodels);
    for (int m = 0; m < nmodels; m++) {
        vtgpol_holder[m].resize(nstates, 0.0);
    }

    completepols_temp.resize(nmodels);
    for (int m = 0; m < nmodels; m++) {
        completepols_temp[m].resize(nstates, -1);
    }

    vtgpol_temp.resize(nmodels);
    for (int m = 0; m < nmodels; m++) {
        vtgpol_temp[m].resize(nstates, 0.0);
    }

    prob_matrix.resize(nstates);
    for (int s = 0; s < nstates; s++) {
        prob_matrix[s].resize(nstates, 0.0);
    }

    inverse_matrix.resize(nstates);
    for (int s = 0; s < nstates; s++) {
        inverse_matrix[s].resize(nstates, 0.0);
    }

    /*wait_and_see_2d.resize(nmodels);
    for (int s = 0; s < nstates; s++) {
    wait_and_see_2d[s].resize(nstates, 0.0);
    }*/

    adj.resize(nstates);
    for (int s = 0; s < nstates; s++) {
        adj[s].resize(nstates, 0.0);
    }

    temp.resize(nstates);
    for (int s = 0; s < nstates; s++) {
        temp[s].resize(nstates, 0.0);
    }

    values.resize(nstates, 0.0);
    vtgpol_temp = vtgpol_holder;
    completepols_temp = completepols_holder;
    model_vals.resize(nmodels, 0.0); // Creates vector for relaxation purposes
    wait_and_see_values.resize(nmodels, 0.0);
    convergence_threshold = epsilon * (1 - discount_factor) / (2 * discount_factor);
    v_old.resize(nstates, 0.0);
    v_new.resize(nstates, 0.0);
    old_policy.resize(nstates, -1);
    new_policy.resize(nstates, -1);
    policy_vtgm.resize(nstates, 0.0);

    v_holder_zeroes.resize(nstates, 0.0);
    v_holder_minus_inf.resize(nstates, -std::numeric_limits<double>::infinity());
}

InfiniteHorizonMMDP::InfiniteHorizonMMDP(const int nstates_in, const int nactions_in,
    const int nmodels_in, const double discount_factor_in,
    const double epsilon_in, const bool equal_rewards,
    const bool equal_initdist) :
    nstates(nstates_in), nactions(nactions_in), nmodels(nmodels_in),
    discount_factor(discount_factor_in), epsilon(epsilon_in) {

    // Randomly assign weights to each model
    weights.reserve(nmodels);
    for (int m = 0; m < nmodels; m++) {
        weights.push_back(1.0 / nmodels);
    }



    double sum_of_elements = 0.0;
    // Randomly assign initial distributions for each state in each model
    initdist.resize(nmodels);
    if (!equal_initdist) {
        for (int m = 0; m < nmodels; m++) {
            initdist[m].resize(nstates);
            for (int s = 0; s < nstates; s++) {
                initdist[m][s] = abs(rand() % 100);
            }
        }

        // Normalize initial distributions so that all distributions add to 1 in each model
        for (int m = 0; m < nmodels; m++) {
            sum_of_elements = std::accumulate(initdist[m].begin(), initdist[m].end(), 0.0);
            for (int s = 0; s < nstates; s++) {
                initdist[m][s] /= sum_of_elements;
            }
        }
    }

    else {
        for (int m = 0; m < nmodels; m++) {
            initdist[m].resize(nstates);
            for (int s = 0; s < nstates; s++) {
                initdist[m][s] = 1.0 / nstates;
            }
        }
    }


    // Appropriately resize the rewards matrix to have a reward
    // for each (m, s, a, t) tuple
    rewards.resize(nmodels);
    for (int m = 0; m < nmodels; m++) {
        rewards[m].resize(nstates);
        for (int s = 0; s < nstates; s++) {
            rewards[m][s].resize(nactions);
        }
    }

    // If unequal rewards are desired, randomly assign each (m, s, a, t) tuple a random reward
    if (!equal_rewards) {
        for (int s = 0; s < nstates; s++) {
            for (int a = 0; a < nactions; a++) {
                for (int m = 0; m < nmodels; m++) {
                    rewards[m][s][a] = abs(double(rand()) / RAND_MAX);
                }
            }

        }

    }

    // If equal rewards are desired, randomly assign each (s, a, t) tuple a random reward
    // but keep reward the same across all models for that (s, a, t) tuple
    else if (equal_rewards) {
        for (int s = 0; s < nstates; s++) {
            for (int a = 0; a < nactions; a++) {
                double val = abs(double(rand()) / RAND_MAX);
                for (int m = 0; m < nmodels; m++) {
                    rewards[m][s][a] = 1.0 * val;
                }

            }

        }

    }

    //  std::default_random_engine generator;
    //std::gamma_distribution<double> distribution(alpha, 1.0);
    // Randomly assign transition probabilities

    tps.resize(nmodels);
    for (int m = 0; m < nmodels; m++) {
        tps[m].resize(nstates);
        for (int s = 0; s < nstates; s++) {
            tps[m][s].resize(nactions);
            for (int a = 0; a < nactions; a++) {
                tps[m][s][a].resize(nstates);
                for (int i = 0; i < nstates; i++) {
                    if (m == 0)
                        tps[0][s][a][i] = abs(double(rand()) / RAND_MAX);
                    else
                        tps[m][s][a][i] = 0.0;
                }
            }
        }
    }

    for (int m = 0; m < 1; m++) {
        for (int s = 0; s < nstates; s++) {
            for (int a = 0; a < nactions; a++) {
                sum_of_elements = std::accumulate(tps[m][s][a].begin(), tps[m][s][a].end(), 0.0);
                for (int snext = 0; snext < nstates; snext++) {
                    tps[m][s][a][snext] /= sum_of_elements;
                }
            }
        }
    }

    // Creates holder matrix for relaxation purposes
    completepols_holder.resize(nmodels);
    for (int m = 0; m < nmodels; m++) {
        completepols_holder[m].resize(nstates, -1);
    }

    vtgpol_holder.resize(nmodels);
    for (int m = 0; m < nmodels; m++) {
        vtgpol_holder[m].resize(nstates, 0.0);
    }

    completepols_temp.resize(nmodels);
    for (int m = 0; m < nmodels; m++) {
        completepols_temp[m].resize(nstates, -1);
    }

    vtgpol_temp.resize(nmodels);
    for (int m = 0; m < nmodels; m++) {
        vtgpol_temp[m].resize(nstates, 0.0);
    }

    prob_matrix.resize(nstates);
    for (int s = 0; s < nstates; s++) {
        prob_matrix[s].resize(nstates, 0.0);
    }

    inverse_matrix.resize(nstates);
    for (int s = 0; s < nstates; s++) {
        inverse_matrix[s].resize(nstates, 0.0);
    }

    wait_and_see_2d.resize(nmodels);
    for (int s = 0; s < nstates; s++) {
        wait_and_see_2d[s].resize(nstates, 0.0);
    }

    adj.resize(nmodels);
    for (int s = 0; s < nstates; s++) {
        adj[s].resize(nstates, 0.0);
    }

    temp.resize(nmodels);
    for (int s = 0; s < nstates; s++) {
        temp[s].resize(nstates, 0.0);
    }

    values.resize(nstates, 0.0);
    vtgpol_temp = vtgpol_holder;
    completepols_temp = completepols_holder;
    model_vals.resize(nmodels, 0.0); // Creates vector for relaxation purposes
    wait_and_see_values.resize(nmodels, 0.0);
    convergence_threshold = epsilon * (1 - discount_factor) / (2 * discount_factor);
    v_old.resize(nstates, 0.0);
    v_new.resize(nstates, 0.0);
    old_policy.resize(nstates, -1);
    new_policy.resize(nstates, -1);
    v_holder_zeroes.resize(nstates, 0.0);
    policy_vtgm.resize(nstates, 0.0);
    v_holder_minus_inf.resize(nstates, -std::numeric_limits<double>::infinity());
}


InfiniteHorizonMMDP::InfiniteHorizonMMDP(const int nstates_in, const int nactions_in,
    const int nmodels_in, const double discount_factor_in,
    const double epsilon_in, const bool equal_rewards,
    const bool equal_initdist, const bool structured) :
    nstates(nstates_in), nactions(nactions_in), nmodels(nmodels_in),
    discount_factor(discount_factor_in), epsilon(epsilon_in) {

    // Randomly assign weights to each model
    weights.reserve(nmodels);
    for (int m = 0; m < nmodels; m++) {
        weights.push_back(1.0 / nmodels);
    }



    double sum_of_elements = 0.0;
    // Randomly assign initial distributions for each state in each model
    initdist.resize(nmodels);
    if (!equal_initdist) {
        for (int m = 0; m < nmodels; m++) {
            initdist[m].resize(nstates);
            for (int s = 0; s < nstates; s++) {
                initdist[m][s] = abs(rand() % 100);
            }
        }

        // Normalize initial distributions so that all distributions add to 1 in each model
        for (int m = 0; m < nmodels; m++) {
            sum_of_elements = std::accumulate(initdist[m].begin(), initdist[m].end(), 0.0);
            for (int s = 0; s < nstates; s++) {
                initdist[m][s] /= sum_of_elements;
            }
        }
    }

    else {
        for (int m = 0; m < nmodels; m++) {
            initdist[m].resize(nstates);
            for (int s = 0; s < nstates; s++) {
                initdist[m][s] = 1.0 / nstates;
            }
        }
    }


    // Appropriately resize the rewards matrix to have a reward for each (m, s, a, t) tuple
    rewards.resize(nmodels);
    for (int m = 0; m < nmodels; m++) {
        rewards[m].resize(nstates);
        for (int s = 0; s < nstates; s++) {
            rewards[m][s].resize(nactions);
        }
    }


    for (int s = 0; s < nstates; s++) {
        for (int a = 0; a < nactions; a++) {
            if (equal_rewards) {
                double reward = 0.0;
                if (structured)
                    reward = (nstates - s - a);
                else
                    reward = abs(double(rand()) / RAND_MAX);
                for (int m = 0; m < nmodels; m++) {
                    rewards[m][s][a] = reward;
                }
            }

            else {
                for (int m = 0; m < nmodels; m++) {
                    if (structured)
                        rewards[m][s][a] = (nstates - s + a);
                    else
                        rewards[m][s][a] = abs(double(rand()) / RAND_MAX);
                }
                
            }

        }

    }

    tps.resize(nmodels);
    for (int m = 0; m < nmodels; m++) {
        tps[m].resize(nstates);
        for (int s = 0; s < nstates; s++) {
            tps[m][s].resize(nactions);
            for (int a = 0; a < nactions; a++) {
                tps[m][s][a].resize(nstates, 0.0);
            }
        }
    }

    if (structured) {
        for (int m = 0; m < nmodels; m++) {
            for (int a = 0; a < nactions; a++) {

                double sampled_prob = abs(double(rand()) / RAND_MAX);
                for (int s = 0; s < nstates; s++) {
                    if (s + 1 == nstates)
                        tps[m][s][a][nstates - 1] = 1;

                    else {
                        tps[m][s][a][s] = sampled_prob;
                        tps[m][s][a][s + 1] = 1 - sampled_prob;
                    }

                }
            }
        }
    }

    else {
        for (int m = 0; m < nmodels; m++) {
            for (int s = 0; s < nstates; s++){
                for (int a = 0; a < nactions; a++) {
                    double total = 0.0;
                    for (int s2 = 0; s2 < nstates; s2++) {
                        tps[m][s][a][s2] = abs(double(rand()) / RAND_MAX);
                        total += tps[m][s][a][s2];
                    }

                    for (int s2 = 0; s2 < nstates; s2++) {
                        tps[m][s][a][s2] = tps[m][s][a][s2] / total;
                    }

                    
                }
            }
        }

    }


    // Creates holder matrix for relaxation purposes
    completepols_holder.resize(nmodels);
    for (int m = 0; m < nmodels; m++) {
        completepols_holder[m].resize(nstates, -1);
    }

    vtgpol_holder.resize(nmodels);
    for (int m = 0; m < nmodels; m++) {
        vtgpol_holder[m].resize(nstates, 0.0);
    }

    completepols_temp.resize(nmodels);
    for (int m = 0; m < nmodels; m++) {
        completepols_temp[m].resize(nstates, -1);
    }

    vtgpol_temp.resize(nmodels);
    for (int m = 0; m < nmodels; m++) {
        vtgpol_temp[m].resize(nstates, 0.0);
    }

    prob_matrix.resize(nstates);
    for (int s = 0; s < nstates; s++) {
        prob_matrix[s].resize(nstates, 0.0);
    }

    inverse_matrix.resize(nstates);
    for (int s = 0; s < nstates; s++) {
        inverse_matrix[s].resize(nstates, 0.0);
    }

    wait_and_see_2d.resize(nmodels);
    for (int s = 0; s < nstates; s++) {
        wait_and_see_2d[s].resize(nstates, 0.0);
    }

    adj.resize(nmodels);
    for (int s = 0; s < nstates; s++) {
        adj[s].resize(nstates, 0.0);
    }

    temp.resize(nmodels);
    for (int s = 0; s < nstates; s++) {
        temp[s].resize(nstates, 0.0);
    }

    values.resize(nstates, 0.0);
    vtgpol_temp = vtgpol_holder;
    completepols_temp = completepols_holder;
    model_vals.resize(nmodels, 0.0); // Creates vector for relaxation purposes
    wait_and_see_values.resize(nmodels, 0.0);
    convergence_threshold = epsilon * (1 - discount_factor) / (2 * discount_factor);
    v_old.resize(nstates, 0.0);
    v_new.resize(nstates, 0.0);
    old_policy.resize(nstates, -1);
    new_policy.resize(nstates, -1);
    v_holder_zeroes.resize(nstates, 0.0);
    policy_vtgm.resize(nstates, 0.0);
    v_holder_minus_inf.resize(nstates, -std::numeric_limits<double>::infinity());
}


void InfiniteHorizonMMDP::updateEpsilon(const double epsilon_in) {
    epsilon = abs(epsilon_in);
    convergence_threshold = epsilon * (1 - discount_factor) / (2 * discount_factor);
}

double InfiniteHorizonMMDP::getConvergenceThreshold() {
    return convergence_threshold;
}

void InfiniteHorizonMMDP::writeToFile(ofstream &fout, InfiniteHorizonMMDP &mmdp) {
    fout << nstates << endl;
    fout << nactions << endl;
    fout << nmodels << endl;

    fout << "Weights:" << endl;
    // Randomly assign weights to each model
    weights.reserve(nmodels);
    for (int m = 0; m < nmodels; m++) {
        fout << 1.0 / nmodels << " ";
    }

    fout << endl;

    fout << "Init_Dist:" << endl;
    for (int m = 0; m < nmodels; m++) {
        for (int s = 0; s < nstates; s++) {
            fout << initdist[m][s] << " ";
        }
        fout << endl;
    }


    // Appropriately resize the rewards matrix to have a reward
    // for each (m, s, a, t) tuple
    fout << "Rewards" << endl;
    for (int m = 0; m < nmodels; m++) {
        for (int s = 0; s < nstates; s++) {
            for (int a = 0; a < nactions; a++) {
                fout << rewards[m][s][a] << " ";
            }
            fout << endl;
        }
        fout << endl;
    }
    fout << endl;

    fout << "TPS:" << endl;
    for (int m = 0; m < nmodels; m++) {
        for (int s = 0; s < nstates; s++) {
            for (int a = 0; a < nactions; a++) {
                for (int i = 0; i < nstates; i++) {
                    fout << tps[m][s][a][i] << " ";
                }
                fout << endl;

            }
            fout << endl;
        }
        fout << endl;
    }


    
}
