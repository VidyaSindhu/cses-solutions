#include <bits/stdc++.h>
using namespace std;

int t = 1;

void dfs(int node, int p, vector<vector<int>> &adj, vector<long long> &value,
         vector<int> &start, vector<int> &end, vector<long long> &lt)
{
    start[node] = t;
    lt[t++] = value[node];

    for (int child : adj[node])
    {
        if (child != p)
        {
            dfs(child, node, adj, value, start, end, lt);
        }
    }

    end[node] = t;
    lt[t++] = value[node];
}

void update(int x, long delta, vector<long long> &BIT){
    for(++x; x < BIT.size(); x += (-x & x)){
        BIT[x] += delta;
    }
}

long long querySum(int x, vector<long long> &BIT){
    long sum = 0;
    for(++x; x > 0; x -= (-x & x)){
        sum += BIT[x];
    }
    return sum;
}

long long rangeSum(int l, int r, vector<long long> &BIT){
    return querySum(r, BIT) - querySum(l-1, BIT);
}


int main()
{
    std::ios::sync_with_stdio(false);
    int n;
    int q;
    cin >> n;
    cin >> q;
    vector<long long> value(n + 1, 0);
    for (int i = 1; i < n + 1; i++)
    {
        cin>>value[i];
    }

    vector<int> start(n + 1, 0);
    vector<int> end(n + 1, 0);
    vector<long long> lt(2 * n + 1, 0);
    vector<long long> bit(2 * n + 2, 0);
    vector<vector<int>> adj(n+1, vector<int>());
    int u;
    int v;
    for (int i = 1; i < n; i++)
    {
        cin >> u;
        cin >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, -1, adj, value, start, end, lt);
    for(int i = 1; i < t; i++){
        update(i, lt[i], bit);
    }
    while(q --> 0){
        int op;
        int node;
        cin >> op;
        cin >> node;
        if(op == 1){
            long long val;
            cin >> val;
            long long delta = val - value[node];
            update(start[node], delta, bit);
            update(end[node], delta, bit);
            value[node] = val;
        }
        else if(op == 2){
            long long ans = rangeSum(start[node], end[node], bit);
            ans = ans/2;
            cout<< ans << endl;
        }
    }
    return 0;
}