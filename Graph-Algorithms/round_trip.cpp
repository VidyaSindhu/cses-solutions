#include <bits/stdc++.h>
using namespace std;

pair<int,int> dfs(int u, int p, int currDepth, vector<int> &parents, vector<int> &depth, vector<vector<int>> &adj) {
    parents[u] = p;
    depth[u] = currDepth;
    for (int v: adj[u]) {
        if (parents[v] == -1) {
            pair<int, int> loop = dfs(v, u, currDepth+1, parents, depth, adj);
            if (loop.first != -1) {
                return loop;
            }
        }
        else if(abs(depth[u] - depth[v]) > 1) {
            return make_pair(u, v);
        }
    }
    return make_pair(-1, -1);
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin>>n>>m;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> parents(n + 1, -1);
    vector<int> depth(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        if (parents[i] == -1) {
            pair<int, int> loop = dfs(i, i, 1, parents, depth, adj);
            // cout<<loop.first<<" "<<loop.second<<endl;;
            if (loop.first != -1) {
                int hops = 0;
                int p = loop.first;
                while(p != loop.second) {
                    hops++;
                    p = parents[p];
                }
                cout<<hops+2<<endl;
                p = loop.first;
                while(p != loop.second) {
                    cout<<p<<" ";
                    p = parents[p];
                }
                cout<<p<<" "<<loop.first;
                return 0;
            }
        }
    }

    cout<<"IMPOSSIBLE"<<endl;
    

    return 0;
}
