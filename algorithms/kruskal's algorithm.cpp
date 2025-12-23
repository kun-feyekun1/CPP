#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, weight;
};

bool cmp(Edge a, Edge b){ return a.weight < b.weight; }

int findParent(int u, vector<int>& parent){
    if(u==parent[u]) return u;
    return parent[u] = findParent(parent[u], parent);
}

int main() {
    int V = 4;
    vector<Edge> edges = {
        {0,1,10},{0,2,6},{0,3,5},{1,3,15},{2,3,4}
    };

    sort(edges.begin(), edges.end(), cmp);

    vector<int> parent(V);
    for(int i=0;i<V;i++) parent[i]=i;

    vector<Edge> mst;

    for(auto e: edges){
        int pu=findParent(e.u,parent);
        int pv=findParent(e.v,parent);
        if(pu!=pv){
            mst.push_back(e);
            parent[pu]=pv;
        }
    }

    cout<<"Edges in MST:\n";
    for(auto e: mst)
        cout<<e.u<<" - "<<e.v<<" weight: "<<e.weight<<endl;

    return 0;
}
