import numpy as np

def print_test_case(nmodels, nstates, nactions, final_rewards, final_tps, num):
    f = open("Buchholz_test_case_" + str(num)+".txt", 'w')
    f.write(str(nstates)+"\n")
    f.write(str(nactions)+"\n")
    f.write(str(nmodels)+"\n\n")
    f.write("Weights:" + "\n")
    for m in range(0, nmodels):
        f.write(str((1.0/nmodels)) + " ")
    f.write("\n\n")

    f.write("Initial_Distribution:" + "\n")
    for m in range(0, nmodels):
        for s in range(0, nstates):
            f.write(str(1.0/nstates) + " ")
        f.write("\n")
    f.write("\n")

    #Write the Rewards
    f.write("Rewards:" + "\n")
    for m in range(0, nmodels):
        for s in range(0, nstates):
            for a in range(0, nactions):
                f.write(str(final_rewards[m, s,a])+" ")
            f.write("\n")
        f.write("\n")
    f.write("\n")

    #Write the transition probabilities
    f.write("TPS:" + "\n")
    for m in range(0, nmodels):
        for s in range(0, nstates):
            for a in range(0, nactions):
                for snext in range(0, nstates):
                    f.write(str(final_tps[m, s,a,snext])+" ")
                f.write("\n")
            f.write("\n")
        f.write("\n")
    f.write("\n")



def test_case_1():
    nmodels = 3
    nstates = 2
    nactions = 2
    tps = np.zeros((nmodels, nstates, nactions,nstates))
    final_rewards = np.zeros((nmodels, nstates, nactions))
    tps[0, 0, 0, 0] = 0
    tps[1, 0, 0, 0] = 0
    tps[2, 0, 0, 0] = 0
    
    tps[0, 0, 0, 1] = 1
    tps[1, 0, 0, 1] = 1
    tps[2, 0, 0, 1] = 1
    
    tps[0, 1, 0, 0] = 1
    tps[1, 1, 0, 0] = 0
    tps[2, 1, 0, 0] = 0
    
    tps[0, 1, 0, 1] = 0
    tps[1, 1, 0, 1] = 1
    tps[2, 1, 0, 1] = 1
    
    
    tps[0, 0, 1, 0] = 1
    tps[1, 0, 1, 0] = 0
    tps[2, 0, 1, 0] = 0
    
    tps[0, 0, 1, 1] = 0
    tps[1, 0, 1, 1] = 1
    tps[2, 0, 1, 1] = 1
        
    tps[0, 1, 1, 0] = 0
    tps[1, 1, 1, 0] = 1
    tps[2, 1, 1, 0] = 0
    
    tps[0, 1, 1, 1] = 1
    tps[1, 1, 1, 1] = 0
    tps[2, 1, 1, 1] = 1
    
    final_rewards[0, 0, 0] =  final_rewards[0, 0, 1] = 2.0/3.0
    final_rewards[0, 1, 0] =  final_rewards[0, 1, 1] = 1.0/3.0
    final_rewards[1, 0, 0] =  final_rewards[1, 0, 1] = 2.0/3.0
    final_rewards[1, 1, 0] =  final_rewards[1, 1, 1] = 2.0/3.0
    final_rewards[2, 0, 0] =  final_rewards[2, 0, 1] = 2.0/3.0
    final_rewards[2, 1, 0] =  final_rewards[2, 1, 1] = 2.0/3.0
    
    print_test_case(3, 2, 2, final_rewards, tps, 1)


def test_case_2():
    nmodels = 4
    nstates = 3
    nactions = 2
    tps = np.zeros((nmodels, nstates, nactions,nstates))
    final_rewards = np.zeros((nmodels, nstates, nactions))
    tps[0, 0, 0, 0] = 0
    tps[1, 0, 0, 0] = 0
    tps[2, 0, 0, 0] = 0
    tps[3, 0, 0, 0] = 1
    
    tps[0, 0, 0, 1] = 1
    tps[1, 0, 0, 1] = 0
    tps[2, 0, 0, 1] = 0
    tps[3, 0, 0, 1] = 0
    
    tps[0, 0, 0, 2] = 0
    tps[1, 0, 0, 2] = 1
    tps[2, 0, 0, 2] = 1
    tps[3, 0, 0, 2] = 0
    
    tps[0, 1, 0, 0] = 0
    tps[1, 1, 0, 0] = 0
    tps[2, 1, 0, 0] = 0
    tps[3, 1, 0, 0] = 0
    
    tps[0, 1, 0, 1] = 0
    tps[1, 1, 0, 1] = 0
    tps[2, 1, 0, 1] = 0
    tps[3, 1, 0, 1] = 1
    
    tps[0, 1, 0, 2] = 1
    tps[1, 1, 0, 2] = 1
    tps[2, 1, 0, 2] = 1
    tps[3, 1, 0, 2] = 0
    
    tps[0, 2, 0, 0] = 0
    tps[1, 2, 0, 0] = 0
    tps[2, 2, 0, 0] = 1
    tps[3, 2, 0, 0] = 0
    
    tps[0, 2, 0, 1] = 0
    tps[1, 2, 0, 1] = 1
    tps[2, 2, 0, 1] = 0
    tps[3, 2, 0, 1] = 1
    
    tps[0, 2, 0, 2] = 1
    tps[1, 2, 0, 2] = 0
    tps[2, 2, 0, 2] = 0
    tps[3, 2, 0, 2] = 0
    
    
    #____________
    
    tps[0, 0, 1, 0] = 0
    tps[1, 0, 1, 0] = 1
    tps[2, 0, 1, 0] = 0
    tps[3, 0, 1, 0] = 0
    
    tps[0, 0, 1, 1] = 1
    tps[1, 0, 1, 1] = 0
    tps[2, 0, 1, 1] = 1
    tps[3, 0, 1, 1] = 0
    
    tps[0, 0, 1, 2] = 0
    tps[1, 0, 1, 2] = 0
    tps[2, 0, 1, 2] = 0
    tps[3, 0, 1, 2] = 1
    
    tps[0, 1, 1, 0] = 0
    tps[1, 1, 1, 0] = 0
    tps[2, 1, 1, 0] = 1
    tps[3, 1, 1, 0] = 0
    
    tps[0, 1, 1, 1] = 1
    tps[1, 1, 1, 1] = 1
    tps[2, 1, 1, 1] = 0
    tps[3, 1, 1, 1] = 0
    
    tps[0, 1, 1, 2] = 0
    tps[1, 1, 1, 2] = 0
    tps[2, 1, 1, 2] = 0
    tps[3, 1, 1, 2] = 1
    
    tps[0, 2, 1, 0] = 0
    tps[1, 2, 1, 0] = 0
    tps[2, 2, 1, 0] = 1
    tps[3, 2, 1, 0] = 0

    tps[0, 2, 1, 1] = 1
    tps[1, 2, 1, 1] = 0
    tps[2, 2, 1, 1] = 0
    tps[3, 2, 1, 1] = 0
    
    tps[0, 2, 1, 2] = 1
    tps[1, 2, 1, 2] = 1
    tps[2, 2, 1, 2] = 0
    tps[3, 2, 1, 2] = 1
 
    
    final_rewards[0, 0, 0] =  final_rewards[0, 0, 1] = 7.0/16.0
    final_rewards[0, 1, 0] =  final_rewards[0, 1, 1] = 1.0/2.0
    final_rewards[0, 2, 0] =  final_rewards[0, 2, 1] = 1.0/16.0
    
    final_rewards[1, 0, 0] =  final_rewards[1, 0, 1] = 1.0/4.0
    final_rewards[1, 1, 0] =  final_rewards[1, 1, 1] = 1.0/4.0
    final_rewards[1, 2, 0] =  final_rewards[1, 2, 1] = 1.0/2.0
    
    final_rewards[2, 0, 0] =  final_rewards[2, 0, 1] = 1.0/9.0
    final_rewards[2, 1, 0] =  final_rewards[2, 1, 1] = 2.0/3.0
    final_rewards[2, 2, 0] =  final_rewards[2, 2, 1] = 2.0/9.0
    
    final_rewards[3, 0, 0] =  final_rewards[3, 0, 1] = 3.0/8.0
    final_rewards[3, 1, 0] =  final_rewards[3, 1, 1] = 3.0/8.0
    final_rewards[3, 2, 0] =  final_rewards[3, 2, 1] = 1.0/4.0
    
    print_test_case(4, 3, 2, final_rewards, tps, 2)


def test_case_3(nstates, nmodels, nactions, test_case):
    tps = np.zeros((nmodels, nstates, nactions,nstates))
    final_rewards = np.zeros((nmodels, nstates, nactions))
    weights = np.zeros((nmodels))
    init_dist = np.zeros((nmodels, nstates))

    # Uniform weights
    for m in range(0, nmodels):
        weights[m] = np.random.uniform(0,1)

    current_sum = sum(weights)
    for m in range(0, nmodels):
        weights[m] = weights[m]/current_sum

    # Uniform initial distribution
    for m in range(0, nmodels):
        for s in range(0, nstates):
            init_dist[m][s] = np.random.uniform(0,1)
        current_sum = sum(init_dist[m])
        for s in range(0, nstates):
            init_dist[m][s] = init_dist[m][s]/current_sum

    # Rewards vary across states, actions, and models. They range from (0, 10).
    for m in range(0, nmodels):
        for s in range(0, nstates):
            for a in range(0, nactions):
                final_rewards[m, s, a] = np.random.uniform(0, 10)
    
    # Transition probabilities vary across intiial states, ending states, actions, and models.
    for m in range(0, nmodels):
        for s1 in range(0, nstates):
            for a in range(0, nactions):
                for s2 in range(0, nstates):
                    tps[m, s1, a, s2] = np.random.uniform(0, 1)
                current_sum = sum(tps[m, s1, a])
                for s2 in range(0, nstates):
                    tps[m, s1, a, s2] = tps[m, s1, a, s2]/current_sum

    # This block of code writes the MMDP to the file in the folder, "Buchholz_Files."
    f = open('Buchholz_Files/Buchholz_random_'+str(nmodels)+'M.'+ str(nstates) +'S.' + str(nactions) + 'A_' +  str(test_case)+   '.txt', 'w')
    f.write(str(nstates)+"\n")
    f.write(str(nactions)+"\n")
    f.write(str(nmodels)+"\n\n")
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

    #Write the Rewards
    f.write("Rewards:" + "\n")
    for m in range(0, nmodels):
        for s in range(0, nstates):
            for a in range(0, nactions):
                f.write(str(final_rewards[m, s,a])+" ")
            f.write("\n")
        f.write("\n")
    f.write("\n")

    #Write the transition probabilities
    f.write("TPS:" + "\n")
    for m in range(0, nmodels):
        for s in range(0, nstates):
            for a in range(0, nactions):
                for snext in range(0, nstates):
                    f.write(str(tps[m, s,a,snext])+" ")
                f.write("\n")
            f.write("\n")
        f.write("\n")
    f.write("\n")

if __name__== "__main__":
    # There are three different test cases reported in the paper by Buchholz
    # When set_of_test_cases = 3, generates the random instances used in our paper
    set_of_test_cases = 3

    if set_of_test_cases == 1:
        test_case_1()
    elif set_of_test_cases == 2:
        test_case_2()
    else:
        problem_sizes = np.zeros((17, 3))
        
        # Modify the desired problem sizes here
        problem_sizes[0] = [2, 2, 2]
        problem_sizes[1] = [3, 3, 3]
        problem_sizes[2] = [2, 5, 2]
        problem_sizes[3] = [10, 5, 2]
        problem_sizes[4] = [2, 10, 3]
        problem_sizes[5] = [2, 10, 10]
        problem_sizes[6] = [5, 5, 5]
        problem_sizes[7] = [3, 20, 4]
        problem_sizes[8] = [3, 50, 3]
        problem_sizes[9] = [5, 50, 5]
        problem_sizes[10] = [3, 100, 4]
        problem_sizes[11] = [3, 200, 4]
        problem_sizes[12] = [3, 300, 4]
        problem_sizes[13] = [3, 500, 4]
        problem_sizes[14] = [3, 700, 4]
        problem_sizes[15] = [5, 800, 5]
        problem_sizes[16] = [3, 1000, 4]
        
        
        for problem_size in problem_sizes:
            for test_case in range(1, 31):
                nmodels = int(problem_size[0])
                nstates = int(problem_size[1])
                nactions = int(problem_size[2])
                test_case_3(nstates, nmodels, nactions, test_case)
