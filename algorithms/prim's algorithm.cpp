// Prim’s Algorithm (Minimum Spanning Tree)

#include <iostream>
#include <vector>
using namespace std;

#define INF 1e9

int main() {
    int V = 5;
    int graph[5][5] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    int key[V], parent[V];
    bool mstSet[V] = {false};

    for(int i=0;i<V;i++) key[i]=INF;
    key[0]=0; parent[0]=-1;

    for(int count=0; count<V-1; count++){
        int u=-1;
        for(int i=0;i<V;i++)
            if(!mstSet[i] && (u==-1 || key[i]<key[u]))
                u=i;

        mstSet[u]=true;

        for(int v=0;v<V;v++){
            if(graph[u][v] && !mstSet[v] && graph[u][v]<key[v]){
                key[v]=graph[u][v];
                parent[v]=u;
            }
        }
    }

    cout<<"Edges in MST:\n";
    for(int i=1;i<V;i++)
        cout<<parent[i]<<" - "<<i<<"  weight: "<<graph[i][parent[i]]<<endl;

    return 0;
}
