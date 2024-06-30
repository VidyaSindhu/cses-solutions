
#include <bits/stdc++.h>
using namespace std;

void dfs(int u, int color, vector<vector<int>> &adj, vector<int> &visited) {
    visited[u] = color;
    for (int v: adj[u]) {
        if (visited[v] == -1) {
            dfs(v, color, adj, visited);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin>>n>>m;

    int roads[m][2];
    for (int i = 0; i < m; i++) {
        cin>>roads[i][0]>>roads[i][1];
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        adj[roads[i][0]-1].push_back(roads[i][1]-1);
        adj[roads[i][1]-1].push_back(roads[i][0]-1);
    }
    vector<int> visited(n, -1);
    int colors = 0;
    for (int i = 0; i < n; i++) {
        if (visited[i] == -1) {
            colors++;
            dfs(i, colors, adj, visited);
        }
    }
    unordered_map<int, int> map;
    for(int i = 0; i< n; i++) {
        map[visited[i]] = i;
    }
    cout<<colors-1<<endl;
    int prev = -1;
    for(auto &pair: map) {
        if (prev == -1) {
            prev = pair.second;
            continue;
        }
        cout<<prev + 1<<" "<<pair.second + 1<<endl;
        prev = pair.second;
    }
    
    return 0;
}
