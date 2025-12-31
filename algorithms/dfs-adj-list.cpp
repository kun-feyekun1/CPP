#include <iostream>
using namespace std;

struct Node {
    int vertex;
    Node* next;
};

Node* adj[10];
int visited[10];
int n;

Node* createNode(int v) {
    Node* node = new Node;
    node->vertex = v;
    node->next = nullptr;
    return node;
}

void addEdge(int src, int dest) {
    Node* node = createNode(dest);
    node->next = adj[src];
    adj[src] = node;
}

void DFS(int v) {
    cout << v << " ";
    visited[v] = 1;

    Node* temp = adj[v];
    while (temp != nullptr) {
        if (!visited[temp->vertex])
            DFS(temp->vertex);
        temp = temp->next;
    }
}

int main() {
    int edges;
    cout << "Enter number of vertices: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        adj[i] = nullptr;
        visited[i] = 0;
    }

    cout << "Enter number of edges: ";
    cin >> edges;

    cout << "Enter edges (src dest):\n";
    for (int i = 0; i < edges; i++) {
        int s, d;
        cin >> s >> d;
        addEdge(s, d);
        addEdge(d, s); // undirected graph
    }

    cout << "DFS traversal starting from vertex 0:\n";
    DFS(0);

    return 0;
}
