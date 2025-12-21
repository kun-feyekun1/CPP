
#include <iostream>
using namespace std;

#define INF 1000000000

/* ===================== DATA STRUCTURES ===================== */

// Adjacency list node
struct Node {
    int to;
    int weight;
    Node* next;
};

// Graph structure
struct Graph {
    int V;
    int directed;
    Node** adj;
};

/* ===================== GRAPH CREATION ===================== */

Node* createNode(int to, int weight) {
    Node* n = new Node;
    n->to = to;
    n->weight = weight;
    n->next = NULL;
    return n;
}

Graph* createGraph(int V, int directed) {
    Graph* g = new Graph;
    g->V = V;
    g->directed = directed;
    g->adj = new Node*[V];

    for (int i = 0; i < V; i++)
        g->adj[i] = NULL;

    return g;
}

/* ===================== BASIC OPERATIONS ===================== */

void addEdge(Graph* g, int u, int v, int w) {
    Node* n = createNode(v, w);
    n->next = g->adj[u];
    g->adj[u] = n;

    if (!g->directed) {
        n = createNode(u, w);
        n->next = g->adj[v];
        g->adj[v] = n;
    }
}

void display(Graph* g) {
    cout << "\nAdjacency List:\n";
    for (int i = 0; i < g->V; i++) {
        cout << i << " -> ";
        Node* t = g->adj[i];
        while (t) {
            cout << "(" << t->to << ", w=" << t->weight << ") ";
            t = t->next;
        }
        cout << endl;
    }
}

/* ===================== BFS ===================== */

void BFS(Graph* g, int start) {
    int* visited = new int[g->V]();
    int* q = new int[g->V];
    int front = 0, rear = 0;

    visited[start] = 1;
    q[rear++] = start;

    cout << "BFS: ";
    while (front < rear) {
        int u = q[front++];
        cout << u << " ";

        Node* t = g->adj[u];
        while (t) {
            if (!visited[t->to]) {
                visited[t->to] = 1;
                q[rear++] = t->to;
            }
            t = t->next;
        }
    }
    cout << endl;

    delete[] visited;
    delete[] q;
}

/* ===================== DFS ===================== */

void DFSUtil(Graph* g, int v, int visited[]) {
    visited[v] = 1;
    cout << v << " ";

    Node* t = g->adj[v];
    while (t) {
        if (!visited[t->to])
            DFSUtil(g, t->to, visited);
        t = t->next;
    }
}

void DFS(Graph* g, int start) {
    int* visited = new int[g->V]();
    cout << "DFS (Recursive): ";
    DFSUtil(g, start, visited);
    cout << endl;
    delete[] visited;
}

void DFSIterative(Graph* g, int start) {
    int* visited = new int[g->V]();
    int* stack = new int[g->V];
    int top = -1;

    stack[++top] = start;
    cout << "DFS (Iterative): ";

    while (top >= 0) {
        int v = stack[top--];
        if (!visited[v]) {
            visited[v] = 1;
            cout << v << " ";

            Node* t = g->adj[v];
            while (t) {
                if (!visited[t->to])
                    stack[++top] = t->to;
                t = t->next;
            }
        }
    }
    cout << endl;

    delete[] visited;
    delete[] stack;
}

/* ===================== CONNECTED COMPONENTS ===================== */

int connectedComponents(Graph* g) {
    int* visited = new int[g->V]();
    int count = 0;

    for (int i = 0; i < g->V; i++) {
        if (!visited[i]) {
            DFSUtil(g, i, visited);
            cout << endl;
            count++;
        }
    }
    delete[] visited;
    return count;
}

/* ===================== CYCLE DETECTION ===================== */

int cycleUndirectedUtil(Graph* g, int v, int visited[], int parent) {
    visited[v] = 1;

    Node* t = g->adj[v];
    while (t) {
        int u = t->to;
        if (!visited[u]) {
            if (cycleUndirectedUtil(g, u, visited, v))
                return 1;
        } else if (u != parent)
            return 1;
        t = t->next;
    }
    return 0;
}

int cycleDirectedUtil(Graph* g, int v, int visited[], int rec[]) {
    visited[v] = 1;
    rec[v] = 1;

    Node* t = g->adj[v];
    while (t) {
        int u = t->to;
        if (!visited[u] && cycleDirectedUtil(g, u, visited, rec))
            return 1;
        else if (rec[u])
            return 1;
        t = t->next;
    }
    rec[v] = 0;
    return 0;
}

int hasCycle(Graph* g) {
    int* visited = new int[g->V]();
    int* rec = new int[g->V]();

    for (int i = 0; i < g->V; i++) {
        if (!visited[i]) {
            if (g->directed) {
                if (cycleDirectedUtil(g, i, visited, rec))
                    return 1;
            } else {
                if (cycleUndirectedUtil(g, i, visited, -1))
                    return 1;
            }
        }
    }
    return 0;
}

/* ===================== TOPOLOGICAL SORT ===================== */

void topologicalSort(Graph* g) {
    int* indeg = new int[g->V]();
    int* q = new int[g->V];
    int front = 0, rear = 0;

    for (int i = 0; i < g->V; i++) {
        Node* t = g->adj[i];
        while (t) {
            indeg[t->to]++;
            t = t->next;
        }
    }

    for (int i = 0; i < g->V; i++)
        if (indeg[i] == 0)
            q[rear++] = i;

    cout << "Topological Order: ";
    while (front < rear) {
        int u = q[front++];
        cout << u << " ";

        Node* t = g->adj[u];
        while (t) {
            if (--indeg[t->to] == 0)
                q[rear++] = t->to;
            t = t->next;
        }
    }
    cout << endl;

    delete[] indeg;
    delete[] q;
}

/* ===================== DIJKSTRA ===================== */

void dijkstra(Graph* g, int src) {
    int* dist = new int[g->V];
    int* used = new int[g->V]();

    for (int i = 0; i < g->V; i++)
        dist[i] = INF;
    dist[src] = 0;

    for (int i = 0; i < g->V; i++) {
        int u = -1;
        for (int j = 0; j < g->V; j++)
            if (!used[j] && (u == -1 || dist[j] < dist[u]))
                u = j;

        used[u] = 1;

        Node* t = g->adj[u];
        while (t) {
            if (dist[u] + t->weight < dist[t->to])
                dist[t->to] = dist[u] + t->weight;
            t = t->next;
        }
    }

    cout << "Dijkstra from " << src << ":\n";
    for (int i = 0; i < g->V; i++)
        cout << "Vertex " << i << " Distance = " << dist[i] << endl;

    delete[] dist;
    delete[] used;
}

/* ===================== MAIN ===================== */

int main() {
    Graph* g = createGraph(6, 1); // directed

    addEdge(g, 0, 1, 2);
    addEdge(g, 0, 4, 1);
    addEdge(g, 1, 2, 3);
    addEdge(g, 2, 3, 6);
    addEdge(g, 4, 2, 2);
    addEdge(g, 4, 5, 4);

    display(g);

    BFS(g, 0);
    DFS(g, 0);
    DFSIterative(g, 0);

    cout << "\nCycle Present: " << (hasCycle(g) ? "Yes" : "No") << endl;

    topologicalSort(g);
    dijkstra(g, 0);

    return 0;
}
