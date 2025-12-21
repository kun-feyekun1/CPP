#include <iostream>
#include <climits>
using namespace std;

#define V 5  // Number of vertices

// Function to find the vertex with minimum distance
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void dijkstra(int graph[V][V], int src) {
    int dist[V];    // Output array. dist[i] = shortest distance from src to i
    bool sptSet[V]; // True if vertex i is included in shortest path tree

    // Step 1: Initialize
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;

    // Step 2: Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet); // Pick minimum distance vertex
        sptSet[u] = true;                  // Mark it as processed

        // Update dist value of adjacent vertices
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // Print the results
    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 0; i < V; i++)
        cout << i << " \t\t " << dist[i] << endl;
}

int main() {
    int graph[V][V] = {
        {0, 10, 0, 5, 0},
        {0, 0, 1, 2, 0},
        {0, 0, 0, 0, 4},
        {0, 3, 9, 0, 2},
        {7, 0, 6, 0, 0}
    };

    int source = 0;
    dijkstra(graph, source);

    return 0;
}
