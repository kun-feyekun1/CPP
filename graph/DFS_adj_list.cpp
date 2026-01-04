
#include <iostream>
using namespace std;

#define MAX 11

struct Node {
    int data;
    Node* next;
};

void addEdge(Node* adj[], int u, int v) {
    Node* n = new Node{v, adj[u]};
    adj[u] = n;
}

void DFS_Util(Node* adj[], int u, bool visited[MAX], bool reachable[MAX]) {
    for (Node* temp = adj[u]; temp != nullptr; temp = temp->next) {
        int v = temp->data;
        if (!visited[v]) {
            visited[v] = true;
            reachable[v] = true;
            DFS_Util(adj, v, visited, reachable);
        }
    }
}

void DFS_Path(Node* adj[], int start, bool reachable[MAX]) {
    bool visited[MAX] = {false};
    visited[start] = true;
    reachable[start] = true;   // ✅ FIX
    DFS_Util(adj, start, visited, reachable);
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

    cout << "DFS Reachable pairs (Adjacency List):\n\n";

    for (int i = 0; i < V; i++) {
        bool reachable[MAX] = {false};
        DFS_Path(adj, i, reachable);

        for (int j = 0; j < V; j++) {
            if (i != j && reachable[j]) {
                cout << i << " -> " << j << endl;
            }
        }
    }

    return 0;
}
