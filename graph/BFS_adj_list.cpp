#include <iostream>
using namespace std;

#define MAX 11

struct Node {
    int data;
    Node* next;
};

void addEdge(Node* adj[], int u, int v) {
    Node* n = new Node;
    n->data = v;
    n->next = adj[u];
    adj[u] = n;
}

void BFS_Path(Node* adj[], int start, bool reachable[MAX]) {
    bool visited[MAX] = {false};
    int queue[MAX];
    int front = 0, rear = 0;

    visited[start] = true;
    reachable[start] = true;   // ✅ FIX
    queue[rear++] = start;

    while (front < rear) {
        int u = queue[front++];

        for (Node* temp = adj[u]; temp != nullptr; temp = temp->next) {
            int v = temp->data;
            if (!visited[v]) {
                visited[v] = true;
                reachable[v] = true;
                queue[rear++] = v;
            }
        }
    }
}

int main() {
    int V = 11;
    Node* adj[MAX] = {nullptr};

    // Directed edges
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

    cout << "Connected vertex pairs (path exists):\n\n";

    for (int i = 0; i < V; i++) {
        bool reachable[MAX] = {false};

        BFS_Path(adj, i, reachable);

        for (int j = 0; j < V; j++) {
            if (i != j && reachable[j]) {
                cout << i << " -> " << j << endl;
            }
        }
    }

    return 0;
}
