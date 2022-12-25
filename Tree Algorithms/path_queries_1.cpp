#include<bits/stdc++.h>
using namespace std;

int timer = 1;

void dfs(vector<vector<int>> &adj, int node, int parent, vector<int> &start, vector<int> &end, 
    vector<long long>& tour, vector<long long> &values){
    start[node] = timer;
    tour[timer++] = values[node];
    for(int v: adj[node]){
        if(v == parent) continue;
        dfs(adj, v, node, start, end, tour, values);
    }
    end[node] = timer;
    tour[timer++] = -values[node];
}

void update(vector<long long> &BIT, int x, int delta){
    for(x++; x < BIT.size(); x += (-x & x)){
        BIT[x] += delta;
    }
}

long long getSum(vector<long long> &BIT, int x){
    long long sum = 0l;
    for(x++; x > 0; x -= (-x & x)){
        sum += BIT[x];
    }

    return sum;
}

int main(){
    int n, q;
    cin>>n>>q;
    vector<vector<int>> adj(n, vector<int>());
    vector<long long> values(n);
    for(int i = 0; i < n; i++){
        cin>>values[i];
    }
    int a, b;
    for(int i = 0; i < n-1; i++){
        cin>>a>>b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> start(n+1, 0);
    vector<int> end(n+1, 0);
    vector<long long> tour(2 * n + 1, 0);
    vector<long long> BIT(tour.size() + 5, 0);

    dfs(adj, 0, -1, start, end, tour, values);
    for(int i = 0; i < tour.size(); i++){
        update(BIT, i, tour[i]);
    }
    // cout<<endl;
    // for(int i = 0; i < tour.size(); i++){
    //     cout<<getSum(BIT, i)<<" ";
    //     // cout<<tour[i]<<" ";
    // }
    // cout<<endl;
    long long c;
    while(q > 0){
        cin>>a;
        if(a == 1){
            cin>>b>>c;
            b--;
            long long delta = c - values[b];
            values[b] = c;
            update(BIT, start[b], delta);
            update(BIT, end[b], -delta);
        }
        else if(a == 2){
            cin>>b;
            b--;
            long long sum = getSum(BIT, start[b]);
            cout<<sum<<endl;
        }
        q--;
    }

    return 0;
}