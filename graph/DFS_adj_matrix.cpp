#include <iostream>
using namespace std;

#define MAX 10

void DFS(int adj[MAX][MAX], bool visited[], int V, int u) {
    visited[u] = true;
    cout << u << " ";

    for (int v = 0; v < V; v++) {
        if (adj[u][v] == 1 && !visited[v]) {
            DFS(adj, visited, V, v);
        }
    }
}

int main() {
    int V = 5;
    int adj[MAX][MAX] = {
        {0,1,1,0,0},
        {1,0,0,1,0},
        {1,0,0,1,1},
        {0,1,1,0,0},
        {0,0,1,0,0}
    };

    bool visited[MAX] = {false};
    DFS(adj, visited, V, 0);
    return 0;
}
