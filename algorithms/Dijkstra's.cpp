#include <iostream>
using namespace std;

#define MAX 11
#define INF 999999

void addEdge(int adj[MAX][MAX], int u, int v, int w) {
    adj[u][v] = w;   // directed weighted edge
}

void Dijkstra(int adj[MAX][MAX], int V, int start, int dist[MAX]) {
    bool visited[MAX] = {false};

    // Step 1: initialize distances
    for (int i = 0; i < V; i++)
        dist[i] = INF;

    dist[start] = 0;

    // Step 2: repeat V times
    for (int count = 0; count < V - 1; count++) {

        // Find unvisited node with smallest distance
        int u = -1;
        int minDist = INF;

        for (int i = 0; i < V; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1) break;

        visited[u] = true;

        // Step 3: relax neighbors
        for (int v = 0; v < V; v++) {
            if (adj[u][v] > 0 && !visited[v]) {
                if (dist[u] + adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + adj[u][v];
                }
            }
        }
    }
}

int main() {
    int V = 11;
    int adj[MAX][MAX] = {0};

    // Weighted edges
    addEdge(adj, 0, 1, 5);   // AA → Jimma
    addEdge(adj, 0, 3, 3);   // AA → Debre Markos
    addEdge(adj, 0, 5, 2);   // AA → Adama
    addEdge(adj, 5, 6, 1);   // Adama → Hawasa
    addEdge(adj, 6, 7, 2);   // Hawasa → Arba Minch
    addEdge(adj, 3, 4, 4);   // Debre Markos → Bahir Dar

    cout << "Shortest path costs:\n\n";

    for (int i = 0; i < V; i++) {
        int dist[MAX];
        Dijkstra(adj, V, i, dist);

        for (int j = 0; j < V; j++) {
            if (i != j && dist[j] != INF) {
                cout << i << " -> " << j
                     << " cost = " << dist[j] << endl;
            }
        }
        cout << endl;
    }

    return 0;
}
