#include <iostream>
using namespace std;

#define MAX 11

void addEdge(int adj[MAX][MAX], int u, int v) {
    adj[u][v] = 1;
}

void BFS_Path(int adj[MAX][MAX], int V, int start, bool reachable[MAX]) {
    bool visited[MAX] = {false};
    int queue[MAX], front = 0, rear = 0;

    visited[start] = true;
    queue[rear++] = start;

    while (front < rear) {
        int u = queue[front++];

        for (int v = 0; v < V; v++) {
            if (adj[u][v] == 1 && !visited[v]) {
                visited[v] = true;
                reachable[v] = true;
                queue[rear++] = v;
            }
        }
    }
}

int main() {
    int V = 11;

    string city[MAX] = {
        "Addis Ababa",
        "Jimma",
        "Nekemte",
        "Debre Markos",
        "Bahir Dar",
        "Adama",
        "Hawasa",
        "Arba Minch",
        "Dire Dawa",
        "Jijiga",
        "Harar"
    };

    int adj[MAX][MAX] = {0};

    addEdge(adj, 0, 1);
    addEdge(adj, 0, 3);
    addEdge(adj, 0, 5);
    addEdge(adj, 1, 2);
    addEdge(adj, 3, 0);
    addEdge(adj, 3, 4);
    addEdge(adj, 4, 3);
    addEdge(adj, 5, 6);
    addEdge(adj, 6, 7);
    addEdge(adj, 8, 9);
    addEdge(adj, 8, 10);

    cout << "Connected city pairs (path exists):\n\n";

    for (int i = 0; i < V; i++) {
        bool reachable[MAX] = {false};
        
        BFS_Path(adj, V, i, reachable);

        for (int j = 0; j < V; j++) {
            if (i != j && reachable[j]) {
                cout << city[i] << " -> " << city[j] << endl;
            }
        }
    }

    return 0;
}
