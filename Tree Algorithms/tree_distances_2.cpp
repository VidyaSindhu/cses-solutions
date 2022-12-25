#include <bits/stdc++.h>
using namespace std;

void dfs1(vector<vector<int>> &adj, int node, int parent, vector<long long> &childs, int depth, vector<long long> &sumDis){
    sumDis[0] += depth;
    for(int v: adj[node]){
        if(v == parent) continue;
        dfs1(adj, v, node, childs, depth+1, sumDis);
        childs[node] += childs[v];
    }
    childs[node]++;
}

void dfs2(vector<vector<int>> &adj, int node, int parent, vector<long long> &childs, vector<long long> &sumDis){
    for(int v: adj[node]){
        if(v == parent) continue;
        sumDis[v] = sumDis[node] - childs[v] + (childs.size() - childs[v]);
        dfs2(adj, v, node, childs, sumDis);
    }
}

int main(){
    int n;
    cin>>n;
    vector<vector<int>> adj(n, vector<int>());
    int a,b;
    for(int i = 0; i < n-1; i++){
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<long long> childs(n, 0);
    vector<long long> sumDis(n, 0);
    dfs1(adj, 0, -1, childs, 0, sumDis);
    dfs2(adj, 0, -1, childs, sumDis);

    for(int i = 0; i < n; i++) cout<<sumDis[i]<<" ";
    return 0;
}
