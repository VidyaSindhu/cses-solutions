#include <bits/stdc++.h>
using namespace std;

int l, timer = 1;
vector<vector<int>> up;
vector<int> tin, tout;

void build(int node, int p, vector<vector<int>> &adj){
    tin[node] = ++timer;
    up[node][0] = p;
    for(int i = 1; i <= l; i++){
        if(up[node][i-1] != -1){
            up[node][i] = up[up[node][i-1]][i-1];
        }
        else{
            up[node][i] = -1;
        }
    }
    for(int child: adj[node]){
        if(child != p){
            build(child, node, adj);
        }
    }
    tout[node] = ++timer;
}

bool isAncestor(int u, int v){
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int getLCA(int u, int v){
    if(isAncestor(u, v)) return u;
    else if(isAncestor(v, u)) return v;
    
    for(int i = l-1; i >= 0; i--){
        if(up[u][i] != -1 && !isAncestor(up[u][i], v)){
            u = up[u][i];
        }
    }
    
    return up[u][0];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int m, n;
    cin>>n>>m;
    l = 19;

    tout.resize(n);
    tin.resize(n);
    up.resize(n, vector<int>(l+1, -1));
    vector<vector<int>> adj(n, vector<int>());

    int u,v;
    for(int i = 0; i < n-1; i++){
        cin>>u;
        u--;
        v = i + 1;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    build(0, -1, adj);

    for(int i = 0; i < m; i++){
        cin>>u>>v;
        u--,v--;
        
        int x = getLCA(u,v);
        cout<<x+1<<endl;
    }
    return 0;
}