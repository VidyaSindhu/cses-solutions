#include <bits/stdc++.h>
using namespace std;
int l;
vector<vector<int>> up;

void build(int node, int p, vector<vector<int>> &adj){
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
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int m, n;
    cin>>n>>m;
    l = 19;
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
        u--;
        
        for(int k = 0; k <= l; k++){
            if(((v >> k) & 1)){
                u = up[u][k];
                if(u == -1) break;
            }
        }
        if(u >= 0)
            cout<<u+1<<endl;
        else cout<<u<<endl;
    }
    return 0;
}