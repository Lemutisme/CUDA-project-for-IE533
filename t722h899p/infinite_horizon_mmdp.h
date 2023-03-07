//
//  infinite_horizon_mmdp.h
//
// Header file that defines the InfiniteHorizonMMDP class. InfiniteHorizonMMDP objects can hold the necessary data that represent the probelm, including transition probabilities, rewards, and more.

#ifndef infinite_horizon_mmdp_h
#define infinite_horizon_mmdp_h
#include <vector>
#include <iostream>
#include <numeric>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>


class InfiniteHorizonMMDP {
public:
    // Default constructor
    InfiniteHorizonMMDP();
    
    InfiniteHorizonMMDP(const std::string  &total_filename, double discount_factor_in, double epsilon_in);
    
    InfiniteHorizonMMDP(const int nstates_in, const int nactions_in,
                        const int nmodels_in, const double discount_factor_in,
                        const double epsilon_in, const bool equal_rewards, const bool equal_initdist);
    
    
    InfiniteHorizonMMDP(const int nstates_in, const int nactions_in,
                        const int nmodels_in, const double discount_factor_in,
                        const double epsilon_in, const bool equal_rewards,
                        const bool equal_initdist, const bool structured);
    
    void updateEpsilon(const double epsilon_in);
    
    double getConvergenceThreshold();

    void writeToFile(std::ofstream &fout, InfiniteHorizonMMDP &mmdp);
    
    
    // Member variables stored inside this class
    // Stores the size of the problem for future reference
    
    int nstates;
    int nactions;
    int nmodels;
    std::vector<double> weights;  // The random weights assigned to each model
    std::vector < std::vector <double> > initdist; // The initial distribution for each state in this MMDP
    // Matrix representing the reards for each (m, s, a, t) tuple
    std::vector < std::vector < std::vector <double> > > rewards;
    // Matrix representing the transition probabilities
    std::vector < std::vector < std::vector < std::vector <double> > > >  tps;
    // Holds the value-to-go matrix (vtgm) from the wait-and-see problem
    std::vector < std::vector <double> > vtgm;
    // Holds the optimal policy for each model (polm) from the wait-and-see problem
    std::vector < std::vector <int> > polm;
    // Will hold the values to go for each relaxation solve temporarily to avoid
    // unnecessary construction/destruction of vectors
    double convergence_threshold;
    
public:
    // Matrix filled out with each relaxation to avoid reconstruction of vectors
    std::vector < std::vector <double> > vtgpol_temp;
    // Holds matrix of all -1's
    std::vector < std::vector <double> > vtgpol_holder;
    // Will hold the relaxed policies for each relaxation solve temporarily to avoid
    // unnecessary construction/destruction of vectors
    std::vector< std::vector<int> > completepols_temp;
    // Holds matrix of all -1's
    std::vector< std::vector<int> > completepols_holder;
    // Will hold the model contributions for each relaxation solve temporarily to avoid
    // unnecessary construction/destruction of vectors
    std::vector<double> model_vals;
    // Holds the wait-and-see objectives values for each model (to be used with some objective functions)
    std::vector<double> wait_and_see_values;
    
    // Extranenous members variables
    std::vector<double> v_old;
    std::vector<double> v_new;
    std::vector<double> v_holder_zeroes;
    std::vector<double> v_holder_minus_inf;
    std::vector<int> old_policy;
    std::vector<int> new_policy;
    std::vector<double> policy_vtgm;
    std::vector< std::vector<double> > prob_matrix;
    std::vector< std::vector<double> > inverse_matrix;
    std::vector<double> values;
    std::vector< std::vector<double> > wait_and_see_2d;
    std::vector< std::vector<double> > adj;
    std::vector< std::vector<double> > temp;
    double max_wait_and_see_val;
    
    
    //Discount factor
    double discount_factor;
    //Epsilon
    double epsilon;
};



#endif /* infinite_horizon_mmdp_h */
