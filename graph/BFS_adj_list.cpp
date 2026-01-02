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

void BFS(Node* adj[], int V, int start) {
    bool visited[MAX] = {false};
    int queue[MAX], front = 0, rear = 0;

    visited[start] = true;
    queue[rear++] = start;

    while (front < rear) {
        int u = queue[front++];
        cout << u << " ";

        for (Node* temp = adj[u]; temp != nullptr; temp = temp->next) {
            int v = temp->data;
            if (!visited[v]) {
                visited[v] = true;
                queue[rear++] = v;
            }
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

    BFS(adj, V, 0);
    return 0;
}
