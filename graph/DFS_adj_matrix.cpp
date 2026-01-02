
#include <iostream>
using namespace std;

#define MAX 11

void addEdge(int adj[MAX][MAX], int u, int v) {
    adj[u][v] = 1;
}

void DFS_Util(int adj[MAX][MAX], int V, int u,
              bool visited[MAX], bool reachable[MAX]) {
    for (int v = 0; v < V; v++) {
        if (adj[u][v] == 1 && !visited[v]) {
            visited[v] = true;
            reachable[v] = true;   // path exists
            DFS_Util(adj, V, v, visited, reachable);
        }
    }
}

void DFS_Path(int adj[MAX][MAX], int V, int start, bool reachable[MAX]) {
    bool visited[MAX] = {false};
    visited[start] = true;
    DFS_Util(adj, V, start, visited, reachable);
}

int main() {
    int V = 11;

    int adj[MAX][MAX] = {0};

    addEdge(adj, 0, 1);   // AA -> Jimma
    addEdge(adj, 0, 3);   // AA -> Debre Markos
    addEdge(adj, 0, 5);   // AA -> Adama

    addEdge(adj, 1, 2);   // Jimma -> Nekemte

    addEdge(adj, 3, 0);   // Debre Markos -> AA
    addEdge(adj, 3, 4);   // Debre Markos -> Bahir Dar

    addEdge(adj, 4, 3);   // Bahir Dar -> Debre Markos

    addEdge(adj, 5, 6);   // Adama -> Hawasa
    addEdge(adj, 6, 7);   // Hawasa -> Arba Minch

    addEdge(adj, 8, 9);   // Dire Dawa -> Jijiga
    addEdge(adj, 8, 10);  // Dire Dawa -> Harar

    cout << "DFS Reachable pairs (Matrix):\n\n";

    for (int i = 0; i < V; i++) {
        bool reachable[MAX] = {false};
        DFS_Path(adj, V, i, reachable);

        for (int j = 0; j < V; j++) {
            if (i != j && reachable[j]) {
                cout << i << " -> " << j << endl;
            }
        }
    }

    return 0;
}
