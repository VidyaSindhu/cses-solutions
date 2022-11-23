#include <bits/stdc++.h>
using namespace std;
int l;
int timer;
vector<int> tin, tout;
vector<vector<int>> parent;

void build(int node, int p, vector<vector<int>> &adj){
    tin[node] = ++timer;
    parent[node][0] = p;
    for(int i = 1; i <= l; i++){
        if(parent[node][i-1] != -1){
            parent[node][i] = parent[parent[node][i-1]][i-1];
        }
        else{
            parent[node][i] = -1;
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
        if(parent[u][i] != -1 && !isAncestor(parent[u][i], v)){
            u = parent[u][i];
        }
    }
    
    return parent[u][0];
}

void dfs(int node, int p, vector<vector<int>> &adj, vector<int> &value){
    long long x = value[node];
    
    for(int child: adj[node]){
        if(child != p){
            dfs(child, node, adj, value);
            x += value[child];
        }
    }
    value[node] = x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int m, n;
    cin>>n>>m;
    
    tout.resize(n);
    tin.resize(n);
    l=19;
    timer = 0;
    parent.resize(n, vector<int>(l+1, -1));    
    
    vector<vector<int>> adj(n, vector<int>());
    int u;
    int v;
    for(int i = 0; i < n-1; i++){
        cin>>u>>v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    build(0, -1, adj);

    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < l+1; j++){
    //         cout<<parent[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    vector<int> value(n, 0);
    for(int i = 0; i < m; i++){
        int a, b;
        cin>>a>>b;
        a--;
        b--;

        int x = getLCA(a, b);
        int p = parent[x][0];
        value[a]++;
        value[b]++;
        value[x]--;
        if(p != -1) value[p]--;
    }
    
    dfs(0, 0, adj, value);
    
    for(int i = 0; i < n; i++){
        cout<<value[i]<<" ";
    }
    
}