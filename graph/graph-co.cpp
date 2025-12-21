#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>

using namespace std;

// Edge structure
struct Edge {
    int to;
    int weight;
};

// Graph class
class Graph {
private:
    int V;
    bool directed;
    vector<vector<Edge>> adj;

    // Helper for DFS
    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        for (auto edge : adj[v]) {
            if (!visited[edge.to]) {
                DFSUtil(edge.to, visited);
            }
        }
    }

    // Helper for cycle detection (undirected)
    bool cycleUndirectedUtil(int v, vector<bool>& visited, int parent) {
        visited[v] = true;

        for (auto edge : adj[v]) {
            int u = edge.to;

            if (!visited[u]) {
                if (cycleUndirectedUtil(u, visited, v))
                    return true;
            } else if (u != parent) {
                return true;
            }
        }
        return false;
    }

    // Helper for cycle detection (directed)
    bool cycleDirectedUtil(int v, vector<bool>& visited, vector<bool>& recStack) {
        visited[v] = true;
        recStack[v] = true;

        for (auto edge : adj[v]) {
            int u = edge.to;

            if (!visited[u] && cycleDirectedUtil(u, visited, recStack))
                return true;
            else if (recStack[u])
                return true;
        }

        recStack[v] = false;
        return false;
    }

public:
    // Constructor
    Graph(int vertices, bool isDirected = false) {
        V = vertices;
        directed = isDirected;
        adj.resize(V);
    }

    // Add vertex
    void addVertex() {
        adj.push_back({});
        V++;
    }

    // Add edge
    void addEdge(int u, int v, int weight = 1) {
        if (u >= V || v >= V || u < 0 || v < 0) {
            cout << "Invalid vertex.\n";
            return;
        }

        adj[u].push_back({v, weight});

        if (!directed) {
            adj[v].push_back({u, weight});
        }
    }

    // Remove edge
    void removeEdge(int u, int v) {
        adj[u].erase(remove_if(adj[u].begin(), adj[u].end(),
            [v](Edge e) { return e.to == v; }), adj[u].end());

        if (!directed) {
            adj[v].erase(remove_if(adj[v].begin(), adj[v].end(),
                [u](Edge e) { return e.to == u; }), adj[v].end());
        }
    }

    // Display graph
    void display() {
        cout << "\nAdjacency List:\n";
        for (int i = 0; i < V; i++) {
            cout << i << " -> ";
            for (auto edge : adj[i]) {
                cout << "(" << edge.to << ", w=" << edge.weight << ") ";
            }
            cout << endl;
        }
    }

    // BFS
    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS: ";
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (auto edge : adj[v]) {
                if (!visited[edge.to]) {
                    visited[edge.to] = true;
                    q.push(edge.to);
                }
            }
        }
        cout << endl;
    }

    // DFS Recursive
    void DFS(int start) {
        vector<bool> visited(V, false);
        cout << "DFS (Recursive): ";
        DFSUtil(start, visited);
        cout << endl;
    }

    // DFS Iterative
    void DFSIterative(int start) {
        vector<bool> visited(V, false);
        stack<int> s;
        s.push(start);

        cout << "DFS (Iterative): ";
        while (!s.empty()) {
            int v = s.top();
            s.pop();

            if (!visited[v]) {
                visited[v] = true;
                cout << v << " ";

                for (auto it = adj[v].rbegin(); it != adj[v].rend(); it++) {
                    if (!visited[it->to])
                        s.push(it->to);
                }
            }
        }
        cout << endl;
    }

    // Connected Components
    int connectedComponents() {
        vector<bool> visited(V, false);
        int count = 0;

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                DFSUtil(i, visited);
                count++;
                cout << endl;
            }
        }
        return count;
    }

    // Cycle detection
    bool hasCycle() {
        vector<bool> visited(V, false);

        if (directed) {
            vector<bool> recStack(V, false);
            for (int i = 0; i < V; i++) {
                if (!visited[i] && cycleDirectedUtil(i, visited, recStack))
                    return true;
            }
        } else {
            for (int i = 0; i < V; i++) {
                if (!visited[i] && cycleUndirectedUtil(i, visited, -1))
                    return true;
            }
        }
        return false;
    }

    // Topological Sort (Kahn's Algorithm)
    void topologicalSort() {
        vector<int> indegree(V, 0);

        for (int i = 0; i < V; i++)
            for (auto edge : adj[i])
                indegree[edge.to]++;

        queue<int> q;
        for (int i = 0; i < V; i++)
            if (indegree[i] == 0)
                q.push(i);

        cout << "Topological Order: ";
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (auto edge : adj[v]) {
                if (--indegree[edge.to] == 0)
                    q.push(edge.to);
            }
        }
        cout << endl;
    }

    // Dijkstra shortest path
    void dijkstra(int src) {
        vector<int> dist(V, numeric_limits<int>::max());
        dist[src] = 0;

        priority_queue<pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>> pq;

        pq.push({0, src});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto edge : adj[u]) {
                int v = edge.to;
                int w = edge.weight;

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "Dijkstra (from " << src << "):\n";
        for (int i = 0; i < V; i++)
            cout << "Vertex " << i << " Distance = " << dist[i] << endl;
    }

    int vertexCount() { return V; }

    int edgeCount() {
        int count = 0;
        for (auto& list : adj)
            count += list.size();
        return directed ? count : count / 2;
    }
};


int main() {
    Graph g(6, true);

    g.addEdge(0, 1, 2);
    g.addEdge(0, 4, 1);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 3, 6);
    g.addEdge(4, 2, 2);
    g.addEdge(4, 5, 4);

    g.display();

    g.BFS(0);
    g.DFS(0);
    g.DFSIterative(0);

    cout << "\nCycle Present: "
         << (g.hasCycle() ? "Yes" : "No") << endl;

    g.topologicalSort();
    g.dijkstra(0);

    cout << "\nVertices: " << g.vertexCount();
    cout << "\nEdges: " << g.edgeCount() << endl;

    return 0;
}
