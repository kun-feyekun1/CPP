#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int V = 5;
    vector<int> adj[5];
    adj[0]={1,2};
    adj[1]={0,3,4};
    adj[2]={0,4};
    adj[3]={1,4};
    adj[4]={1,2,3};

    vector<bool> visited(V,false);
    queue<int> q;

    int start=0;
    visited[start]=true;
    q.push(start);

    cout<<"BFS Traversal: ";
    while(!q.empty()){
        int u=q.front(); q.pop();
        cout<<u<<" ";
        for(int v: adj[u]){
            if(!visited[v]){
                visited[v]=true;
                q.push(v);
            }
        }
    }
    cout<<endl;
    return 0;
}
