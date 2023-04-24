/* Main
 */
#include <iostream>
#include <string>
#include <memory>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <unistd.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <sys/stat.h>
#include "lib/ssp.h"

using namespace std;
using namespace std::chrono;


/**
 * Print help for command line parameters
 */
void usageCommand(string message = "") {
    cerr << message << std::endl;
    cout << "Usage: ./binnary.out [-a <int>] < input_data.txt" << endl;
    cout << "-a Type of algorithm for APSP" << endl
            << "\t0: NAIVE FLOYD WARSHALL" << endl
            << "\t1: CUDA NAIVE FLOYD WARSHALL" << endl
            << "\t2: CUDA BLOCKED FLOYD WARSHALL" << endl;
    cout << "-h for help" << endl;
    exit(-1);
}

/**
 * Parse command line parameters
 *
 * @param argc: number of parameters
 * @param argv: parameters
 *
 * @return: Algorithm type
 */
graphAPSPAlgorithm parseCommand(int argc, char** argv) {
    int opt;
    graphAPSPAlgorithm algorithm;
    while ((opt = getopt(argc, argv, "ha:")) != -1) {
        switch (opt) {
        case 'a':
            algorithm = static_cast<graphAPSPAlgorithm>(atoi(optarg));
            break;
        case 'h':
            usageCommand();
            break;
        default:
            usageCommand("Unknown argument !!!");
        }
    }
    if (algorithm > graphAPSPAlgorithm::CUDA_BLOCKED_FW ||
            algorithm < graphAPSPAlgorithm::NAIVE_FW)
        usageCommand("Incorrect value for -a !!!");
    return algorithm;
}

/**
 * Read data from input
 */
unique_ptr<graphAPSPTopology> readData(int maxValue) {
    int nvertex, nedges;
    int v1, v2, mean, sigma, value;
    cin >> nvertex >> nedges;

    /* Init data graph */
    unique_ptr<graphAPSPTopology> data;
    data = unique_ptr<graphAPSPTopology>(new graphAPSPTopology(nvertex));
    fill_n(data->pred.get(), nvertex * nvertex, -1);
    fill_n(data->graph.get(), nvertex * nvertex, maxValue);

    /* Load data from standard input */
    for (int i = 0; i < nedges; ++i) {
        cin >> v1 >> v2 >> mean >> sigma;
        value = mean + 3 * sigma;
        data->graph[v1 * nvertex + v2] = value;
        data->pred[v1 * nvertex + v2] = v1;
    }

    /* Path from vertex v to vertex v is 0 */
    for (unsigned int i = 0; i < nvertex; ++i) {
        data->graph[i * nvertex + i] = 0;
        data->pred[i * nvertex + i] = -1;
    }
    return data;
}



void saveMatrixJson(const string& filename, const unique_ptr<int[]>& matrix, int n, int max) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "[";
        for (int i = 0; i < n; ++i) {
            file << "[";
            for (int j = 0; j < n; ++j) {
                if (max > matrix[i * n + j])
                    file << matrix[i * n + j];
                else
                    file << -1;
                if (j != n - 1) file << ",";
            }
            if (i != n - 1)
                file << "],\n";
            else
                file << "]";
        }
        file << "]";
        file.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

string getCurrentDateTime() {
    auto now = system_clock::now();
    auto in_time_t = system_clock::to_time_t(now);
    auto in_tm = *localtime(&in_time_t);
    ostringstream oss;
    oss << put_time(&in_tm, "%Y%m%d_%H%M%S");
    return oss.str();
}

void saveDataJson(const unique_ptr<graphAPSPTopology>& graph, int maxValue) {
    string datetime = getCurrentDateTime();
    string log_path = "./log/";
    string folder_name = log_path + datetime + "_nvertex_" + to_string(graph->nvertex);
    mkdir(folder_name.c_str(), 0777);

    string graph_file = folder_name + "/graph.json";
    string predecessors_file = folder_name + "/predecessors.json";

    saveMatrixJson(graph_file, graph->graph, graph->nvertex, maxValue);
    saveMatrixJson(predecessors_file, graph->pred, graph->nvertex, maxValue);
}

int main(int argc, char **argv) {
    int maxValue = MAX_DISTANCE;
    auto algorithm = parseCommand(argc, argv);
    auto graph = readData(maxValue);

    /* Compute APSP */
    high_resolution_clock::time_point start = high_resolution_clock::now();
    apsp(graph, algorithm);
    high_resolution_clock::time_point stop = high_resolution_clock::now();

    /* Save graph and predecessors */
    saveDataJson(graph, maxValue);

    /* Print computation time */
    auto duration = duration_cast<milliseconds>(stop - start).count();
    cout << "Compute time: " << duration << " ms" << endl;
    return 0;
}
