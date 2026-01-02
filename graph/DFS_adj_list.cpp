#include <iostream>
using namespace std;

#define MAX 10

struct Node {
    int data;
    Node* next;
};

void addEdge(Node* adj[], int u, int v) {
    Node* n1 = new Node{v, adj[u]};
    adj[u] = n1;

    Node* n2 = new Node{u, adj[v]};
    adj[v] = n2;
}

void DFS(Node* adj[], bool visited[], int u) {
    visited[u] = true;
    cout << u << " ";

    for (Node* temp = adj[u]; temp != nullptr; temp = temp->next) {
        if (!visited[temp->data]) {
            DFS(adj, visited, temp->data);
        }
    }
}

int main() {
    int V = 5;
    Node* adj[MAX] = {nullptr};

    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 2, 3);
    addEdge(adj, 2, 4);

    bool visited[MAX] = {false};
    DFS(adj, visited, 0);
    return 0;
}
