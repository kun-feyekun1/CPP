#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;  // adjust for larger n if needed (but backtracking is slow for n>15-18)

// Graph as adjacency matrix (1 = edge exists, 0 = no edge)
int graph[MAXN][MAXN];
int path[MAXN];       // stores current path
bool visited[MAXN];
int N;                // number of vertices

// Utility function to check if vertex v can be added at index 'pos' in the path
bool isSafe(int v, int pos) {
    // Check if this vertex is an adjacent vertex of the previously added vertex
    if (graph[path[pos-1]][v] == 0)
        return false;

    // Check if the vertex has already been included in the path
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

// Recursive utility function to solve Hamiltonian Cycle problem
bool hamCycleUtil(int pos) {
    // base case: If all vertices are included in the path
    if (pos == N) {
        // And if there is an edge from the last vertex to the first vertex
        if (graph[path[pos-1]][path[0]] == 1)
            return true;
        else
            return false;
    }

    // Try different vertices as the next candidate
    for (int v = 1; v < N; v++) {   // we start from vertex 1 (0 is fixed as start)
        if (isSafe(v, pos)) {
            path[pos] = v;

            if (hamCycleUtil(pos + 1))
                return true;

            // If adding vertex v doesn't lead to a solution → backtrack
            path[pos] = -1;
        }
    }

    return false;
}

// Main function to solve Hamiltonian Cycle problem
bool hamCycle() {
    // Initialize path array
    memset(path, -1, sizeof(path));

    // Fix the starting point as vertex 0
    path[0] = 0;

    if (hamCycleUtil(1) == false) {
        cout << "No Hamiltonian Cycle exists in this graph\n";
        return false;
    }

    // Print the solution
    cout << "Hamiltonian Cycle exists. One possible cycle:\n";
    for (int i = 0; i < N; i++)
        cout << path[i] << " → ";
    cout << path[0] << "\n";  // back to start

    return true;
}

int main() {
    cout << "Enter number of vertices (N): ";
    cin >> N;

    cout << "Enter the adjacency matrix (" << N << "x" << N << "):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> graph[i][j];
        }
    }

    cout << "\nTrying to find Hamiltonian Cycle...\n\n";
    hamCycle();

    return 0;
}