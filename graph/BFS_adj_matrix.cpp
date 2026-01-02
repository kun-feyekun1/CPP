
#include <iostream>
using namespace std;

#define MAX 11

// 0, AA, 1,jimma, 2,nekemte, 3,debre markos, 4,bahir dar,
// 5,adama,6,hawasa,7, arba minch, 8, diredawa, 19,jijiga,10, harar

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

    int adj[MAX][MAX] = {
        {0,1,0,1,0,1,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0},
        {1,0,0,0,1,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,0,0},
        {0,0,0,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0}
    };

    cout << "Connected vertex pairs (path exists):\n\n";

    for (int i = 0; i < V; i++) {
        bool reachable[MAX] = {false};

        BFS_Path(adj, V, i, reachable);

        for (int j = 0; j < V; j++) {
            if (i != j && reachable[j]) {
                cout << i << " -> " << j << endl;
            }
        }
    }

    return 0;
}
