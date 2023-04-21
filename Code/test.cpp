#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <algorithm>
#include <random>
#include <cmath>
#include <stack>

using namespace std;

class Graph {
public:
    Graph(int nodes) : N(nodes) {}

    void addEdge(int u, int v, const vector<int> &w, const vector<double> &p) {
        graph[u].push_back({v, w, p});
    }

    vector<int> topologicalSortUtil(int v, vector<bool> &visited, stack<int> &Stack) {
        visited[v] = true;
        if (graph.find(v) != graph.end()) {
            for (const auto &[node, w_s, p_s] : graph[v]) {
                if (!visited[node]) {
                    topologicalSortUtil(node, visited, Stack);
                }
            }
        }
        Stack.push(v);
        vector<int> sortedList;
        while (!Stack.empty()) {
            sortedList.push_back(Stack.top());
            Stack.pop();
        }
        return sortedList;
    }

    vector<int> topologicalSort(int s) {
        vector<bool> visited(N, false);
        stack<int> Stack;
        for (int i = 0; i < N; ++i) {
            if (!visited[i]) {
                topologicalSortUtil(s, visited, Stack);
            }
        }
        vector<int> sortedList;
        while (!Stack.empty()) {
            sortedList.push_back(Stack.top());
            Stack.pop();
        }
        return sortedList;
    }

    // Continue implementing other methods from the Python code

private:
    int N;
    map<int, vector<tuple<int, vector<int>, vector<double>>>> graph;
};

int main() {
    Graph g(8);
    g.addEdge(0, 1, {3, 5, 8}, {0.5, 0.4, 0.1});
    g.addEdge(1, 7, {35, 65}, {0.98, 0.02});
    g.addEdge(0, 2, {20, 25}, {0.99, 0.01});
    g.addEdge(2, 7, {20, 28}, {0.99, 0.01});
    g.addEdge(0, 4, {6, 8, 10}, {0.2, 0.4, 0.4});
    g.addEdge(4, 5, {20, 25, 30}, {0.2, 0.6, 0.2});
    g.addEdge(4, 6, {10, 15, 40}, {0.05, 0.85, 0.1});
    g.addEdge(6, 7, {5, 10, 20}, {0.05, 0.8, 0.15});
    g.addEdge(6, 5, {2, 3}, {0.5, 0.5});
    g.addEdge(5, 7, {10, 12, 15}, {0.2, 0.6, 0.2});
    g.addEdge(2, 3, {2, 3}, {0.25, 0.75});
    g.addEdge(5, 3, {2, 3}, {0.5, 0.5});
    g.addEdge(6, 3, {5, 6}, {0.5, 0.5});
    g.addEdge(3, 7, {15, 27}, {0.99, 0.01});

    vector<int> sortedList = g.topologicalSort(0);

    for (const auto &v : sortedList) {
        cout << v << " ";
    }

    cout << endl;

    return 0;
}

