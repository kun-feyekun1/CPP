#include <iostream>
using namespace std;

#define MAX 10

int graph[MAX][MAX];
int visited[MAX];
int n;  // number of vertices

void DFS(int v) {
    cout << v << " ";
    visited[v] = 1;

    for (int i = 0; i < n; i++) {
        if (graph[v][i] == 1 && visited[i] == 0) {
            DFS(i);
        }
    }
}

int main() {
    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter adjacency matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> graph[i][j];

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    cout << "DFS traversal starting from vertex 0:\n";
    DFS(0);

    return 0;
}
