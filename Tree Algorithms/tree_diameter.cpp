#include<bits/stdc++.h>
using namespace std;

int a = -1;
int maxD = INT_MIN;
void dfs(int node, int parent, vector<vector<int>> &adj, int d){
    if(maxD < d){
        maxD = d;
        a = node;
    }
    
    for(int child: adj[node]){
        if(child == parent) continue;
        dfs(child, node, adj, d + 1);
    }
}

void dfs1(int node, int parent, vector<vector<int>> &adj, vector<int> &d, int depth){
    d[node] = depth;
    for(int c: adj[node]){
        if(c == parent) continue;
        dfs1(c, node, adj, d, depth + 1);
    }
}
int main() {
    int n;
    cin>>n;
    vector<vector<int>> adj(n, vector<int>());
    int u,v;
    for(int i = 0; i < n-1; i++){
        cin>>u>>v;
        u--,v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    a = -1;
    dfs(0, -1, adj, 0);

    int first = a;
    maxD = INT_MIN;

    dfs(a, -1, adj, 0);
    
    cout<<maxD<<endl;
    return 0;
}
