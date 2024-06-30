#include <bits/stdc++.h>
using namespace std;



int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin>>n>>m;

    vector<vector<pair<int,long>>> adj(n+1);
    for (int i = 0; i < m; i++) {
        int u, v;
        long w;
        cin>>u>>v>>w;
        adj[u].push_back({v, w});
    }

    vector<bool> seen(n+1, false);
    vector<long> dis(n+1, LONG_MAX);

    dis[1] = 0;

    multiset<pair<long,int>> s;
    s.insert({0 , 1});

    while(!s.empty()) {
        pair <long , int> p = *s.begin();
        s.erase(s.begin());

        int u = p.second;
        long currDis = p.first;

        if (seen[u]) continue;
        
        seen[u] = true;

        for(auto &node: adj[u]) {
            int v = node.first;
            long weigth = node.second;
            if (dis[v] > currDis + weigth) {
                dis[v] = currDis + weigth;
                s.insert({dis[v], v});
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout<<dis[i]<<" ";
    }

    return 0;
}