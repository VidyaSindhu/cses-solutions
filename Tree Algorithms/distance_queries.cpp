#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> up;
vector<int> depth;
vector<int> tin, tout;
int timer = 1, l;

void dfs(int node, int parent, int d, vector<vector<int>> &adj){
    tin[node] = ++timer;

    depth[node] = d;
    up[node][0] = parent;
    for(int i = 1; i <= l; i++){
        if(up[node][i-1] != -1){
            up[node][i] = up[up[node][i-1]][i-1];
        }
    }

    for(int child: adj[node]){
        if(child != parent){
            // depth[child] = depth[node] + 1;
            dfs(child, node, d+1, adj);
        }
    }
    tout[node] = ++timer;
}

bool isAncestor(int u, int v){
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int getLCA(int u, int v){
    if(isAncestor(u, v)) return u;
    else if(isAncestor(u, v)) return v;

    for(int i = l-1; i >= 0; i--){
        if(up[u][i] != -1 && !isAncestor(up[u][i], v)){
            u = up[u][i];
        }
    }
    return up[u][0];
}

int main(){
    std::ios::sync_with_stdio(false);
    int n, m;
    cin>>n>>m;
    l = 19;
    tin.resize(n);
    tout.resize(n);
    up.resize(n, vector<int>(l+1, -1));
    depth.resize(n, 0);
    
    vector<vector<int>> adj(n, vector<int>());
    int u,v;
    for(int i = 0; i < n-1; i++){
        cin>>u>>v;
        u--,v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0, 0, 0, adj);

    for(int i = 0; i < m; i++){
        cin>>u>>v;
        u--,v--;
        int x = getLCA(u,v);
        cout<< depth[v] + depth[u] - 2 * depth[x] <<endl;
    }

    return 0;
}
