#include <bits/stdc++.h>
using namespace std;

bool dfs(int u, int color, vector<int> &colored, vector<vector<int>> &adj)
{
    colored[u] = color;
    for (int v: adj[u]) {
        if (colored[v] == -1) {
            if (!dfs(v, color^1, colored, adj)) {
                return false;
            }
        } else if (colored[v] == color) {
            return false;
        }
    }
    return true;
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

    vector<int> colored(n + 1, -1);

    for (int i = 1; i < n+1; i++)
    {
        if (colored[i] == -1)
        {
            bool isBiPartitioningDone = dfs(i, 0, colored, adj);
            
            if (!isBiPartitioningDone) {
                cout<<"IMPOSSIBLE"<<endl;
                return 0;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout<<colored[i+1]+1<<" ";
    }

    return 0;
}
