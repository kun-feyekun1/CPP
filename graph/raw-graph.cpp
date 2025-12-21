#include <iostream>
using namespace std;

/* ---------- STRUCT DEFINITIONS ---------- */

// Node in adjacency list
struct Node {
    int vertex;
    int weight;
    Node* next;
};

// Graph structure
struct Graph {
    int vertices;
    int directed;
    Node** adjList;
};

/* ---------- FUNCTION DECLARATIONS ---------- */

Graph* createGraph(int vertices, int directed);
Node* createNode(int v, int w);
void addEdge(Graph* graph, int src, int dest, int weight);
void removeEdge(Graph* graph, int src, int dest);
void displayGraph(Graph* graph);
void BFS(Graph* graph, int start);
void DFSUtil(Graph* graph, int v, int visited[]);
void DFS(Graph* graph, int start);
int countEdges(Graph* graph);

/* ---------- FUNCTION DEFINITIONS ---------- */

// Create graph
Graph* createGraph(int vertices, int directed) {
    Graph* graph = new Graph;
    graph->vertices = vertices;
    graph->directed = directed;

    graph->adjList = new Node*[vertices];
    for (int i = 0; i < vertices; i++)
        graph->adjList[i] = NULL;

    return graph;
}

// Create adjacency node
Node* createNode(int v, int w) {
    Node* node = new Node;
    node->vertex = v;
    node->weight = w;
    node->next = NULL;
    return node;
}

// Add edge
void addEdge(Graph* graph, int src, int dest, int weight) {
    if (src < 0 || dest < 0 || src >= graph->vertices || dest >= graph->vertices) {
        cout << "Invalid vertex\n";
        return;
    }

    Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    if (!graph->directed) {
        newNode = createNode(src, weight);
        newNode->next = graph->adjList[dest];
        graph->adjList[dest] = newNode;
    }
}

// Remove edge
void removeEdge(Graph* graph, int src, int dest) {
    Node* temp = graph->adjList[src];
    Node* prev = NULL;

    while (temp != NULL && temp->vertex != dest) {
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL) {
        if (prev == NULL)
            graph->adjList[src] = temp->next;
        else
            prev->next = temp->next;
        delete temp;
    }

    if (!graph->directed) {
        temp = graph->adjList[dest];
        prev = NULL;

        while (temp != NULL && temp->vertex != src) {
            prev = temp;
            temp = temp->next;
        }

        if (temp != NULL) {
            if (prev == NULL)
                graph->adjList[dest] = temp->next;
            else
                prev->next = temp->next;
            delete temp;
        }
    }
}

// Display graph
void displayGraph(Graph* graph) {
    cout << "\nAdjacency List:\n";
    for (int i = 0; i < graph->vertices; i++) {
        cout << i << " -> ";
        Node* temp = graph->adjList[i];
        while (temp != NULL) {
            cout << "(" << temp->vertex << ", w=" << temp->weight << ") ";
            temp = temp->next;
        }
        cout << endl;
    }
}

// BFS (array queue)
void BFS(Graph* graph, int start) {
    int* visited = new int[graph->vertices]();
    int* queue = new int[graph->vertices];

    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    cout << "BFS: ";
    while (front < rear) {
        int v = queue[front++];
        cout << v << " ";

        Node* temp = graph->adjList[v];
        while (temp != NULL) {
            if (!visited[temp->vertex]) {
                visited[temp->vertex] = 1;
                queue[rear++] = temp->vertex;
            }
            temp = temp->next;
        }
    }
    cout << endl;

    delete[] visited;
    delete[] queue;
}

// DFS helper
void DFSUtil(Graph* graph, int v, int visited[]) {
    visited[v] = 1;
    cout << v << " ";

    Node* temp = graph->adjList[v];
    while (temp != NULL) {
        if (!visited[temp->vertex])
            DFSUtil(graph, temp->vertex, visited);
        temp = temp->next;
    }
}

// DFS
void DFS(Graph* graph, int start) {
    int* visited = new int[graph->vertices]();
    cout << "DFS: ";
    DFSUtil(graph, start, visited);
    cout << endl;
    delete[] visited;
}

// Count edges
int countEdges(Graph* graph) {
    int count = 0;
    for (int i = 0; i < graph->vertices; i++) {
        Node* temp = graph->adjList[i];
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
    }
    return graph->directed ? count : count / 2;
}

/* ---------- MAIN FUNCTION ---------- */

int main() {
    Graph* graph = createGraph(5, 0); // undirected

    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 4, 3);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 3, 4);
    addEdge(graph, 3, 4, 5);

    displayGraph(graph);

    BFS(graph, 0);
    DFS(graph, 0);

    cout << "Vertices: " << graph->vertices << endl;
    cout << "Edges: " << countEdges(graph) << endl;

    removeEdge(graph, 1, 3);
    displayGraph(graph);

    return 0;
}
