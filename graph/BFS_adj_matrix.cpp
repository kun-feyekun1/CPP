#include <iostream>
using namespace std;

#define MAX 10

void BFS(int adj[MAX][MAX], int V, int start) {
    bool visited[MAX] = {false};
    int queue[MAX], front = 0, rear = 0;

    visited[start] = true;
    queue[rear++] = start;

    while (front < rear) {
        int u = queue[front++];
        cout << u << " ";

        for (int v = 0; v < V; v++) {
            if (adj[u][v] == 1 && !visited[v]) {
                visited[v] = true;
                queue[rear++] = v;
            }
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

    BFS(adj, V, 0);
    return 0;
}
