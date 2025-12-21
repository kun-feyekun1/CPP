
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
private:
    int vertices;
    bool directed;
    vector<vector<pair<int, int>>> adjList;

public:
    // Constructor
    Graph(int v, bool isDirected = false) {
        vertices = v;
        directed = isDirected;
        adjList.resize(vertices);
    }

    // Add a new vertex
    void addVertex() {
        adjList.push_back({});
        vertices++;
        cout << "Vertex added successfully.\n";
    }

    // Add edge
    void addEdge(int u, int v, int weight = 1) {
        if (u >= vertices || v >= vertices || u < 0 || v < 0) {
            cout << "Invalid vertex number.\n";
            return;
        }

        adjList[u].push_back({v, weight});

        if (!directed) {
            adjList[v].push_back({u, weight});
        }
    }

    // Remove edge
    void removeEdge(int u, int v) {
        if (u >= vertices || v >= vertices) {
            cout << "Invalid vertex.\n";
            return;
        }

        adjList[u].erase(
            remove_if(adjList[u].begin(), adjList[u].end(),
                      [v](pair<int, int> edge) { return edge.first == v; }),
            adjList[u].end()
        );

        if (!directed) {
            adjList[v].erase(
                remove_if(adjList[v].begin(), adjList[v].end(),
                          [u](pair<int, int> edge) { return edge.first == u; }),
                adjList[v].end()
            );
        }
    }

    // Remove vertex
    void removeVertex(int v) {
        if (v >= vertices) {
            cout << "Invalid vertex.\n";
            return;
        }

        adjList.erase(adjList.begin() + v);
        vertices--;

        for (auto &list : adjList) {
            list.erase(
                remove_if(list.begin(), list.end(),
                          [v](pair<int, int> edge) { return edge.first == v; }),
                list.end()
            );

            for (auto &edge : list) {
                if (edge.first > v)
                    edge.first--;
            }
        }

        cout << "Vertex removed successfully.\n";
    }

    // Display graph
    void display() {
        cout << "\nGraph adjacency list:\n";
        for (int i = 0; i < vertices; i++) {
            cout << i << " -> ";
            for (auto edge : adjList[i]) {
                cout << "(" << edge.first << ", w=" << edge.second << ") ";
            }
            cout << endl;
        }
    }

    // BFS traversal
    void BFS(int start) {
        vector<bool> visited(vertices, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS: ";
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (auto edge : adjList[node]) {
                if (!visited[edge.first]) {
                    visited[edge.first] = true;
                    q.push(edge.first);
                }
            }
        }
        cout << endl;
    }

    // DFS traversal
    void DFS(int start) {
        vector<bool> visited(vertices, false);
        stack<int> s;

        s.push(start);

        cout << "DFS: ";
        while (!s.empty()) {
            int node = s.top();
            s.pop();

            if (!visited[node]) {
                visited[node] = true;
                cout << node << " ";

                for (auto it = adjList[node].rbegin();
                     it != adjList[node].rend(); it++) {
                    if (!visited[it->first])
                        s.push(it->first);
                }
            }
        }
        cout << endl;
    }

    // Count vertices
    int getVertexCount() {
        return vertices;
    }

    // Count edges
    int getEdgeCount() {
        int count = 0;
        for (auto list : adjList)
            count += list.size();

        return directed ? count : count / 2;
    }
};


int main() {
    Graph g(5, false); // Undirected graph

    g.addEdge(0, 1, 2);
    g.addEdge(0, 4, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 4);
    g.addEdge(3, 4, 5);

    g.display();

    g.BFS(0);
    g.DFS(0);

    cout << "Vertices: " << g.getVertexCount() << endl;
    cout << "Edges: " << g.getEdgeCount() << endl;

    g.removeEdge(1, 3);
    g.display();

    g.removeVertex(2);
    g.display();

    return 0;
}
