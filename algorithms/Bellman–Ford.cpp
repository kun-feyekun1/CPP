#include <iostream>
#include <climits>
using namespace std;

int main() {
    int V = 4;   // number of vertices
    int E = 4;   // number of edges

    // Edge list representation
    int src[E] = {0, 0, 1, 2};
    int dest[E] = {1, 2, 2, 3};
    int weight[E] = {4, 5, -3, 4};

    int source = 0;

    // Distance array
    int dist[V];

    // Step 1: Initialize distances
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }
    dist[source] = 0;

    // Step 2: Relax all edges V-1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            if (dist[src[j]] != INT_MAX &&
                dist[src[j]] + weight[j] < dist[dest[j]]) {

                dist[dest[j]] = dist[src[j]] + weight[j];
            }
        }
    }

    // Step 3: Check for negative weight cycles
    bool negativeCycle = false;
    for (int j = 0; j < E; j++) {
        if (dist[src[j]] != INT_MAX &&
            dist[src[j]] + weight[j] < dist[dest[j]]) {

            negativeCycle = true;
            break;
        }
    }

    // Output
    if (negativeCycle) {
        cout << "Negative weight cycle detected!" << endl;
    } else {
        cout << "Vertex   Distance from Source" << endl;
        for (int i = 0; i < V; i++) {
            cout << i << " \t\t ";
            if (dist[i] == INT_MAX)
                cout << "INF";
            else
                cout << dist[i];
            cout << endl;
        }
    }

    return 0;
}
