import numpy as np

# These transition probabilities were based on information from the original Machine Repair paper.
def generate_nominal():
    tps = np.zeros((10, 4, 10))
    tps[:, 0, :] = [[0.2,	0.8,	0,	0,	0	,0,	0,	0,	0,	0],
                    [0,	0.2,	0.8,	0,	0,	0,	0,	0,	0,	0],
                    [0,	0,	0.20,	0.8,	0,	0,	0,	0,	0,	0],
                    [0,	0,	0,	0.20,	0.80,	0,	0,	0,	0,	0],
                    [0,	0,	0,	0,	0.20,	0.80,	0,	0,	0,	0],
                    [0,	0,	0,	0,	0,	0.20,	0.8,	0, 0,	0],
                    [0,	0,	0,	0,	0,	0,	0.20,	0.8,	0,	0],
                    [0,	0,	0,	0,	0,	0,	0, 1,	0,	0],
                    [0.8,	0,	0,	0,	0,	0,	0, 0, 0.2, 0],
                    [0,	0,	0,	0, 0,	0,	0,	0, 0,	1]]

    tps[:, 1, :] = [[0, 0.3, 0, 0, 0, 0, 0, 0, 0.6, 0.1 ],
                    [0, 0, 0.3, 0, 0, 0, 0, 0, 0.6, 0.1],
                    [0, 0, 0.3, 0.30, 0, 0, 0, 0, 0.6, 0.1],
                    [0, 0, 0, 0, 0.30, 0, 0, 0, 0.6, 0.1],
                    [0,0, 0, 0, 0, 0.30, 0, 0, 0.6, 0.1],
                    [0, 0, 0, 0, 0, 0, 0.30, 0, 0.6, 0.1],
                    [0, 0, 0, 0, 0, 0, 0, 0.30, 0.6, 0.1],
                    [0, 0, 0, 0, 0, 0, 0, 0.3, 0.6, 0.1],
                    [0, 0, 0, 0, 0, 0, 0, 0, 1.0, 0],
                    [0, 0, 0, 0, 0, 0, 0, 0, 0.6, 0.4]]

    tps[:, 2, :] = [[0, 0.3, 0, 0, 0, 0, 0, 0, 0.576, 0.124],
                    [0, 0, 0.3, 0, 0, 0, 0, 0, 0.576, 0.124],
                    [0, 0, 0.3, 0.30, 0, 0, 0, 0, 0.576, 0.124],
                    [0, 0, 0, 0, 0.30, 0, 0, 0, 0.576, 0.124],
                    [0, 0, 0, 0, 0, 0.30, 0, 0, 0.576, 0.124],
                    [0, 0, 0, 0, 0, 0, 0.30, 0, 0.576, 0.124],
                    [0, 0, 0, 0, 0, 0, 0, 0.30, 0.576, 0.124],
                    [0, 0, 0, 0, 0, 0, 0, 0.3, 0.576, 0.124],
                    [0, 0, 0, 0, 0, 0, 0, 0, 1.0, 0],
                    [0, 0, 0, 0, 0, 0, 0, 0, 0.576, 0.424]]

    tps[:, 3, :] = [[0, 0.3, 0, 0, 0, 0, 0, 0, 0.6286, 0.0714],
                    [0, 0, 0.3, 0, 0, 0, 0, 0, 0.6286, 0.0714],
                    [0, 0, 0.3, 0.30, 0, 0, 0, 0, 0.6286, 0.0714],
                    [0, 0, 0, 0, 0.30, 0, 0, 0, 0.6286, 0.0714],
                    [0, 0, 0, 0, 0, 0.30, 0, 0, 0.6286, 0.0714],
                    [0, 0, 0, 0, 0, 0, 0.30, 0, 0.6286, 0.0714],
                    [0, 0, 0, 0, 0, 0, 0, 0.30, 0.6286, 0.0714],
                    [0, 0, 0, 0, 0, 0, 0, 0.3, 0.6286, 0.0714],
                    [0, 0, 0, 0, 0, 0, 0, 0, 1.0, 0],
                    [0, 0, 0, 0, 0, 0, 0, 0, 0.6286, 0.3714]]


    return tps

if __name__ == '__main__':
    # Array containing desired concentration parameters; add or delete as desired
    # We used 1, 5, 9
    array = [1, 5, 9]
    
    # Array containing desired number of models; add or delete as desired
    # We used 10, 30, 100
    mods = [10, 30, 100]
    
    for conc in array:
        for nmodels in mods:
            for test_num in range(3, 4):
                nstates = 10
                nactions = 4
                rewards = np.zeros((nmodels, nstates, nactions))

                for m in range(0, nmodels):
                    for a in range(0, nactions):
                        rewards[m][7][a] = -10.0
                        rewards[m][8][a] = -2.0
                        rewards[m][9][a] = -20.0

                weights = np.zeros(nmodels)
                for i in range(0, nmodels):
                    weights[i] = 1.0/nmodels

                init_dist = np.zeros((nmodels, nstates))
                for m in range(0, nmodels):
                    for s in range(0, nstates):
                        init_dist[m][s] = 1.0/nstates

                nominal_tps = generate_nominal()

                for s in range(0, nstates):
                    for a in range(0, nactions):
                        for next in range(0, nstates):
                            if nominal_tps[s, a, next] == 0.0:
                                nominal_tps[s, a, next] = 0.00000000001

                tps = np.zeros((nmodels, nstates, nactions, nstates))

                for s1 in range(0, nstates):
                    for a in range(0, nactions):
                        matrix = np.random.dirichlet(conc * nominal_tps[s1, a, :], nmodels)

                        for m in range(0, nmodels):
                            tps[m, s1, a, :] = matrix[m]

                # Opens the file that will contain the MMDP data
                f = open("Machine_Maintenance/Delage_conc_" + str(conc) + "_" + str(nmodels) + "_models_test_" + str(test_num) + ".txt", 'w')
                f.write(str(nstates) + "\n")
                f.write(str(nactions) + "\n")
                f.write(str(nmodels) + "\n\n")

                f.write("Weights:" + "\n")
                for m in range(0, nmodels):
                    f.write(str(weights[m]) + " ")
                f.write("\n\n")

                f.write("Initial_Distribution:" + "\n")
                for m in range(0, nmodels):
                    for s in range(0, nstates):
                        f.write(str(init_dist[m, s]) + " ")
                    f.write("\n")
                f.write("\n")

                # Write the Rewards
                f.write("Rewards:" + "\n")
                for m in range(0, nmodels):
                    for s in range(0, nstates):
                        for a in range(0, nactions):
                            f.write(str(rewards[m, s, a]) + " ")
                        f.write("\n")
                    f.write("\n")
                f.write("\n")

                # Write the transition probabilities
                f.write("TPS:" + "\n")
                for m in range(0, nmodels):
                    for s in range(0, nstates):
                        for a in range(0, nactions):
                            for snext in range(0, nstates):
                                f.write(str(tps[m, s, a, snext]) + " ")
                            f.write("\n")
                        f.write("\n")
                    f.write("\n")
                f.write("\n")



