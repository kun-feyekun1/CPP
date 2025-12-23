#include <iostream>
#include <vector>
using namespace std;

#define INF 1e9

int main() {
    int V = 4; // number of vertices
    int graph[4][4] = {
        {0, 5, INF, 10},
        {INF, 0, 3, INF},
        {INF, INF, 0, 1},
        {INF, INF, INF, 0}
    };

    int dist[4][4];
    for(int i=0;i<V;i++)
        for(int j=0;j<V;j++)
            dist[i][j] = graph[i][j];

    for(int k=0;k<V;k++)
        for(int i=0;i<V;i++)
            for(int j=0;j<V;j++)
                if(dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    cout << "Shortest distances between all pairs:\n";
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            if(dist[i][j]==INF) cout<<"INF ";
            else cout<<dist[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
