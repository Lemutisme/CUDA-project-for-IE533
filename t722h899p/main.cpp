//
//  main.cpp
//

/* Helps read in or create MMDP problem instances */

#include <iostream>
#include <ctime>
#include <numeric>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <math.h>
#include <cassert>
#include "infinite_horizon_mmdp.h"

using namespace std;

// Change the desired input filename as desired
const string input_file = "HIV_test_72_models.txt";

double time_limit_in_seconds = 300.0;

int main() {
    ios_base::sync_with_stdio(false); // Make reading and writing input/output faster
    cout << setprecision(11); // Set the floating point precision
    srand(static_cast<unsigned int>(time(NULL))); // Reset random seed

    
    double discount_factor = 0.97;
    double epsilon_for_wait_and_see = 1.0;
    
    // Create infinite-horizon MMDP data object by reading in file
    //InfiniteHorizonMMDP infinite_horizon_mmdp
    InfiniteHorizonMMDP(input_file, discount_factor, epsilon_for_wait_and_see);


    return 0;
}
