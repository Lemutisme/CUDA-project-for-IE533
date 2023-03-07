import os
import numpy as np


class InfiniteHorizonMMDP:

    def __init__(self):
        self.nmodels = 0
        self.nstates = 0
        self.nactions = 0

    def __init__(self, filename, discount_factor_in, epsilon_in):
        f = open(filename, "r")
        contents = f.read().split() # Read in all the contents of the file and delimit by space

        self.nstates, self.nactions, self.nmodels = int(contents[0]), int(contents[1]), int(contents[2])
        self.weights = np.zeros(self.nmodels)
        self.init_dist = np.zeros((self.nmodels, self.nstates))
        self.rewards = np.zeros((self.nmodels, self.nstates, self.nactions))
        self.tps = np.zeros((self.nmodels, self.nstates, self.nactions, self.nstates))
        self.discount_factor = discount_factor_in
        self.epsilon = epsilon_in

        weights_data = contents[4:4 + self.nmodels]

        for m in range(0, len(weights_data)):
            self.weights[m] = float(weights_data[m])

        contents = contents[5 + self.nmodels:]
        init_dist_data = contents[0: self.nmodels * self.nstates]

        for i in range(len(init_dist_data)):
            self.init_dist[int(i/self.nstates), int(i % self.nstates)] = float(init_dist_data[i])

        contents = contents[self.nmodels*self.nstates + 1:]
        reward_data = contents[0: self.nmodels * self.nstates * self.nactions]

        for m in range(0, self.nmodels):
            for s in range(0, self.nstates):
                for a in range(0, self.nactions):
                    self.rewards[m, s, a] = float(reward_data[m * s * a])

        contents = contents[self.nmodels * self.nstates * self.nactions + 1:]

        for m in range(0, self.nmodels):
            for s1 in range(0, self.nstates):
                for a in range(0, self.nactions):
                    for s2 in range(0, self.nstates):
                        self.tps[m, s1, a, s2] = float(contents[m * s1 * a * s2])


if __name__ == '__main__':
    filename = "HIV_model.txt" # Change filename as desired
    mmdp = InfiniteHorizonMMDP(filename, 0.97, 1)   # Current discount factor = 0.97 and epsilon = 1


