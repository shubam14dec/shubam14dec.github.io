#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
    vector<vector<int>> adjacencyMatrix;
    int nodes, edges;
public:
    Graph(int nodes, int edges) {
        this->nodes = nodes;
        this->edges = edges;
        adjacencyMatrix.resize(nodes, vector<int>(nodes, 0));
    }

    void buildGraph() {
        for (int i = 0; i < edges; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            adjacencyMatrix[u][v] = w;
            adjacencyMatrix[v][u] = w;
        }
    }

    vector<int> breadthFirstSearch(int start) {
        vector<bool> visited(nodes, false);
        vector<int> traversal;
        queue<int> q;
        q.push(start);
        visited[start] = true;
        while (!q.empty()) {
            int currentNode = q.front();
            traversal.push_back(currentNode);
            q.pop();
            for (int neighbor = 0; neighbor < nodes; ++neighbor) {
                if (adjacencyMatrix[currentNode][neighbor] && !visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
        return traversal;
    }
};