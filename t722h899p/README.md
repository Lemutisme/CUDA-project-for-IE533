# Infinite-Horizon MMDPs

This code repository contains the files we used to create the test instances for infinte-horizon MMDPs. These problems were based off of case studies previously published in the literature. We use a medical decision-making problem for the initiation of HIV therapy, a machine maintenance problem, and a set of randomly constructed instances. We also include C++ code and Python code that can read in an MMDP data file such that others can experiment with new methods for solving them. All MMDP files that will be generated with the included scripts are all in the same format and style.

## Using the Code
If using a Python file, you can install any necessary dependency, "library_name" via the following the following command in the terminal: "pip install library_name".

1) Random Instances (RI) from Buchholz & Scheftelowitsch (2019)
Creates random MMDP instances of various problem sizes. A set of thirty example 8-model, 8-state, 8-action MMDP files are included in the zip file "Buchholz 8M-8S-8A.zip". When the script is run, it will generate random MMDP instances using the structure described in Buchholz & Scheftelowitsch (2019) that will have the problem sizes designated by the vector "problem_sizes". Each entry in the "problem_sizes" vector will yield 30 distinct MMDP files that have the corresponding number of states, actions, and models. All files will be written to a folder called "Buchholz_Files" which must be created by the user in the working directory. Currently, the 17 different problem sizes specified in Buchholz & Scheftelowitsch (2019) are part of the "problem_sizes" vector. This will yield 30 * 17 = 510 files. 
Dependency: numpy
run 'python3 buchholz_random_model_writer.py'

2) Machine Maintenance Problems from Delage & Mannor (2010)
Creates machine maintenance instances of various model sizes and concentration parameters based off the above paper. There are currently three concentration parameters (1, 5, 9) and three different model sizes (10, 30, 100). This script will generate files to a folder calledl, "Machine_Maintenance" which must be created by the user in the working directory. 30 files will be written to that folder for each concentration parameter and model size. Currently, this will lead to 3 * 3 * 30 = 270 files. 
Dependency: numpy.
run 'python3 machine_repair_model_writer.py'

3) HIV Therapy Example from Shechter et al. (2008)
Creates an HIV initiation MMDP file with name "HIV_test.txt". An example MMDP file is incldued as "HIV_test_72_models.txt". 
Dependency: numpy.
run 'python3 HIV_model_writer.py'

4) Reading in MMDP Files Using C++
The necessary files are 'main.cpp', 'infinte_horizon_mmdp.h', and 'infinite_horizon_mmdp.cpp'. No output expected.
run 1) 'g++ -Wall -Werror main.cpp infinite_horizon_mmdp.cpp -o out' and then 2) './out' in the terminal

5) Reading in MMDP Files Using Python
Analogous to Section 4 above. No output expected. Dependencies: numpy, os.
Run 'python3 infinite_horizon_mmdp.py'


## Authors

* **Vinayak S. Ahluwalia** 

**Lauren N. Steimle**  

**Brian T. Denton** 

## Funding
This work was supported by the National Science Foundation under grant numbers DGE-1256260 (Steimle) and CMMI-1462060 (Denton); any opinions, findings, and conclusions or recommendations expressed in this material are those of the authors and do not necessarily reflect the views of the National Science Foundation. 

## Attribution

If using the code in this package, please cite the following article where we discuss these methods: 

Ahluwalia, Steimle, and Denton, "Policy-based branch-and-bound for infinite-horizon Multi-model Markov decision processes". 2020.



