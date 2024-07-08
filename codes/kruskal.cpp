#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class UnionFind {
public:
    vector<int> rank, parent, setSize;
    UnionFind(int n) {
        parent.resize(n + 1);
        setSize.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            setSize[i] = 1;
        }
    }

    int findSet(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findSet(parent[node]);
    }

    void unionByRank(int u, int v) {
        int rootU = findSet(u);
        int rootV = findSet(v);
        if (rootU == rootV) return;
        if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else if (rank[rootV] < rank[rootU]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }

    void unionBySize(int u, int v) {
        int rootU = findSet(u);
        int rootV = findSet(v);
        if (rootU == rootV) return;
        if (setSize[rootU] < setSize[rootV]) {
            parent[rootU] = rootV;
            setSize[rootV] += setSize[rootU];
        } else {
            parent[rootV] = rootU;
            setSize[rootU] += setSize[rootV];
        }
    }
    
    int getSize(int node) {
        return setSize[findSet(node)];
    }
};

class Graph {
    vector<vector<int>> adjMatrix;
    int numNodes, numEdges;
public:
    Graph(int numNodes, int numEdges) {
        this->numNodes = numNodes;
        this->numEdges = numEdges;
        adjMatrix.resize(numNodes, vector<int>(numNodes, 0));
    }

    void initializeGraph() {
        for (int i = 0; i < numEdges; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            adjMatrix[u][v] = w;
            adjMatrix[v][u] = w;
        }
    }

    int kruskalMST() {
        int mstWeight = 0;
        UnionFind uf(numNodes);
        vector<pair<int, pair<int, int>>> edges;
        for (int i = 0; i < numNodes; ++i) {
            for (int j = 0; j < i; ++j) {
                if (adjMatrix[i][j]) {
                    edges.push_back({adjMatrix[i][j], {i, j}});
                }
            }
        }
        sort(edges.begin(), edges.end());
        for (const auto& edge : edges) {
            int weight = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;
            if (uf.findSet(u) != uf.findSet(v)) {
                mstWeight += weight;
                uf.unionBySize(u, v);
            }
        }
        return mstWeight;
    }
};

int main() {
    int n, e;
    cin >> n >> e;
    Graph g(n, e);
    g.initializeGraph();
    cout << g.kruskalMST() << endl;
    return 0;
}
