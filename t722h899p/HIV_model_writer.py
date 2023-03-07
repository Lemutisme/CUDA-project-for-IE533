import numpy as np


# Uses the rewards model, rewards scenario, transitions scenario, and survival model information to construct the MMDP for the appropriate HIV model. The following values are taken from Shechter's work on the HIV model. Consult the original work for more information.
def get_rewards_and_tps(rewards_model, rewards_scenario_number, tps_scenario_number,
                        survival_model):
    #                       0-49, 50-199, 200-349, >=350, Death, Initiate
    scenario1_tp_wait = np.array([[0.1, 0, 0, 0, 0.9, 0],
                                  [0.55, 0.05, 0, 0, 0.4, 0],
                                  [0.05, 0.5, 0.4, 0, 0.05, 0],
                                  [0.08, 0.1, 0.2, 0.6, 0.02, 0],
                                  [0, 0, 0, 0, 1, 0],
                                  [0, 0, 0, 0, 0, 1]])

    #                     0-49, 50-199, 200-349, >=350, Death, Initiate
    scenario2_tp_wait = np.array([[0.1, 0, 0, 0, 0.9, 0],
                                  [0.2, 0.1, 0, 0, 0.7, 0],
                                  [0.1, 0.3, 0.1, 0, 0.5, 0],
                                  [0.1, 0.2, 0.3, 0.1, 0.3, 0],
                                  [0, 0, 0, 0, 1, 0],
                                  [0, 0, 0, 0, 0, 1]])

    #                     0-49, 50-199, 200-349, >=350, Death, Initiate
    scenario3_tp_wait = np.array([[0.7, 0, 0, 0, 0.3, 0],
                                  [0.2, 0.7, 0, 0, 0.1, 0],
                                  [0.075, 0.2, 0.7, 0, 0.025, 0],
                                  [0.01, 0.05, 0.131, 0.8, 0.009, 0],
                                  [0, 0, 0, 0, 1, 0],
                                  [0, 0, 0, 0, 0, 1]])

    #                     0-49, 50-199, 200-349, >=350, Death, Initiate
    scenario4_tp_wait = np.array([[0.9, 0, 0, 0, 0.1, 0],
                                  [0.075, 0.9, 0, 0, 0.025, 0],
                                  [0.01, 0.081, 0.9, 0, 0.009, 0],
                                  [0.015, 0.03, 0.054, 0.9, 0.001, 0],
                                  [0, 0, 0, 0, 1, 0],
                                  [0, 0, 0, 0, 0, 1]])

    #                       0-49, 50-199, 200-349, >=350, Death, Initiate
    scenario1_tp_initiate = np.array([[0, 0, 0, 0, 0, 1],
                                      [0, 0, 0, 0, 0, 1],
                                      [0, 0, 0, 0, 0, 1],
                                      [0, 0, 0, 0, 0, 1],
                                      [0, 0, 0, 0, 1, 0],
                                      [0, 0, 0, 0, 0, 1]])

    #                       0-49, 50-199, 200-349, >=350, Death, Initiate
    scenario2_tp_initiate = np.array([[0, 0, 0, 0, 0, 1],
                                      [0, 0, 0, 0, 0, 1],
                                      [0, 0, 0, 0, 0, 1],
                                      [0, 0, 0, 0, 0, 1],
                                      [0, 0, 0, 0, 1, 0],
                                      [0, 0, 0, 0, 0, 1]])

    #                       0-49, 50-199, 200-349, >=350, Death, Initiate
    scenario3_tp_initiate = np.array([[0, 0, 0, 0, 0, 1],
                                      [0, 0, 0, 0, 0, 1],
                                      [0, 0, 0, 0, 0, 1],
                                      [0, 0, 0, 0, 0, 1],
                                      [0, 0, 0, 0, 1, 0],
                                      [0, 0, 0, 0, 0, 1]])

    #                       0-49, 50-199, 200-349, >=350, Death, Initiate
    scenario4_tp_initiate = np.array([[0, 0, 0, 0, 0, 1],
                                      [0, 0, 0, 0, 0, 1],
                                      [0, 0, 0, 0, 0, 1],
                                      [0, 0, 0, 0, 0, 1],
                                      [0, 0, 0, 0, 1, 0],
                                      [0, 0, 0, 0, 0, 1]])

    rewards = np.zeros((6, 2))
    scenario_numbers = np.array([1, 2, 3])

    remaining_life_years = np.array([6.34, 11.61, 17.25, 24.79, 0, 0])

    Schackman_onHAART_utilities = np.array([[0.79, 0.82, 0.87, 0.87],
                                            [0.62, 0.64, 0.68, 0.68],
                                            [0.44, 0.46, 0.49, 0.49]])

    Freedberg_onHAART_utilities = np.array([[0.71, 0.76, .85, 0.85],
                                            [0.55, 0.59, 0.66, 0.66],
                                            [0.4, 0.42, 0.47, 0.47]])

    # transitions 1, survival: baseline, schackman, 0.9 utilities

    if rewards_model == "Schackman":
        rewards[0, 0] =  0.88
        rewards[1, 0] = 0.91
        rewards[2, 0] =  0.97
        rewards[3, 0] =  0.97
        rewards[4, 0] = 0
        rewards[5, 0] = 0
        rewards[4, 1] = 0
        rewards[5, 1] = 0
        for s in range(0, 4):
            rewards[s, 1] = remaining_life_years[s] * survival_model  * Schackman_onHAART_utilities[
                rewards_scenario_number, s]


    elif rewards_model == "Freedberg":
        rewards[0, 0] = 0.79
        rewards[1, 0] = 0.84
        rewards[2, 0] = 0.94
        rewards[3, 0] = 0.94
        rewards[4, 0] = 0
        rewards[5, 0] = 0
        rewards[4, 1] = 0
        rewards[5, 1] = 0
        for s in range(0, 4):
            rewards[s, 1] = remaining_life_years[s] * survival_model * Freedberg_onHAART_utilities[
                rewards_scenario_number, s]

    if tps_scenario_number == 1:
        return (scenario1_tp_wait, scenario1_tp_initiate, rewards)
    elif tps_scenario_number == 2:
        return (scenario2_tp_wait, scenario2_tp_initiate, rewards)
    elif tps_scenario_number == 3:
        return (scenario3_tp_wait, scenario3_tp_initiate, rewards)
    elif tps_scenario_number == 4:
        return (scenario4_tp_wait, scenario4_tp_initiate, rewards)


if __name__ == "__main__":
    nmodels = 72
    nstates = 6
    nactions = 2
    rewards_models = np.array(["Schackman", "Freedberg"])
    survival_models = np.array([0.9, 1, 1.1])

    final_tps = np.zeros((nmodels, nstates, nactions, nstates))
    final_rewards = np.zeros((nmodels, nstates, nactions))
    count = 0
    
    # Will write all rewards/probabilities to CSV file; does not contain relevant MMDP data

    for rewards_model in rewards_models:
        for survival_model in survival_models:
            for tps_scenario_number in range(1, 5):
                for rewards_scenario_number in range(0, 3):
                    (tp_wait, tp_initiate, rewards) = get_rewards_and_tps(rewards_model, rewards_scenario_number,
                                                                          tps_scenario_number, survival_model)
                    tps = np.zeros((nstates, nactions, nstates))

                    for s in range(0, nstates):
                        for snext in range(0, nstates):
                            final_tps[count, s, 0, snext] = tp_wait[s][snext]

                    for s in range(0, nstates):
                        for snext in range(0, nstates):
                            final_tps[count, s, 1, snext] = tp_initiate[s][snext]

                    for s in range(0, nstates):
                        for a in range(0, nactions):
                            final_rewards[count, s, a] = rewards[s, a]

                    count = count + 1

    # Name of file to which MMDP data will be written
    f = open("HIV_model.txt", 'w')
    
    
    f.write(str(6) + "\n")
    f.write(str(2) + "\n")
    f.write(str(nmodels) + "\n\n")
    
    # Write the weights
    f.write("Weights:" + "\n")
    for m in range(0, nmodels):
        f.write(str((1.0 / nmodels)) + " ")
    f.write("\n\n")

    # Write the initial distribution
    f.write("Initial_Distribution:" + "\n")
    for m in range(0, nmodels):
        for s in range(0, 4):
            f.write(str((1.0 / 4)) + " ")
        for s in range(0, 2):
            f.write(str(0) + " ")
        f.write("\n")
    f.write("\n")

    # Write the Rewards
    f.write("Rewards:" + "\n")
    for m in range(0, nmodels):
        for s in range(0, nstates):
            for a in range(0, nactions):
                f.write(str(final_rewards[m, s, a]) + " ")
            f.write("\n")
        f.write("\n")
    f.write("\n")

    # Write the transition probabilities
    f.write("TPS:" + "\n")
    for m in range(0, nmodels):
        for s in range(0, nstates):
            for a in range(0, nactions):
                for snext in range(0, nstates):
                    f.write(str(final_tps[m, s, a, snext]) + " ")
                f.write("\n")
            f.write("\n")
        f.write("\n")
    f.write("\n")
