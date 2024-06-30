#include <bits/stdc++.h>
using namespace std;

bool bfs(int u, vector<vector<int>> &adj, vector<int> &parents) {
    parents[u] = u;
    queue<int> q;
    q.push(u);
    while(q.size()>0) {
        int top = q.front();
        q.pop();
        for (int v: adj[top]) {
            if (parents[v] == -1) {
                parents[v] = top;
                if (v == 1) {
                    return true;
                }
                q.push(v);  
            }
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin>>n>>m;

    int connections[m][2];
    for (int i = 0; i < m; i++) {
        cin>>connections[i][0]>>connections[i][1];
    }

    vector<vector<int>> adj(n+1);
    for (int i = 0; i < m; i++) {
        adj[connections[i][0]].push_back(connections[i][1]);
        adj[connections[i][1]].push_back(connections[i][0]);
    }

    vector<int> parents(n+1, -1);

    bool isPossibleToSendMessage = bfs(n, adj, parents);

    if (isPossibleToSendMessage) {
        int numberOfHops = 0;
        int i = 1;
        while(i != n) {
            i = parents[i];
            numberOfHops++;
        }
        cout<<numberOfHops+1<<endl;
        i = 1;
        while(i != n) {
            cout<<i<<" ";
            i = parents[i];
        }
        cout<<i<<endl;
        return 0;
    }

    if (!isPossibleToSendMessage) {
        cout<<"IMPOSSIBLE"<<endl;
    }

    return 0;
}