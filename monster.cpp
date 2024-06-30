#include <bits/stdc++.h>
using namespace std;

int directions[4][3] = {{0, 1, 0}, {1, 0, 1}, {0, -1, 2}, {-1, 0, 3}};

char nextDirection(int i) {
  if (i == 0) {
    return 'R';
  }
  if (i == 1) {
    return 'D';
  }
  if (i == 2) {
    return 'L';
  }
  return 'U';
}

pair<int,int> bfs(queue<pair<int, int>> &queue, vector<vector<char>> &graph) {
    int n = graph.size();
    int m = graph[0].size();
    while(!queue.empty()) {
        pair<int,int> top = queue.front(); queue.pop();
        int x = top.first;
        int y = top.second;
        for (auto &direction: directions) {
            int nx = x + direction[0];
            int ny = y + direction[1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && graph[nx][ny] == '.') {
                if (graph[x][y] == 'M') {
                    graph[nx][ny] = 'M';
                } 
                else if (graph[x][y] == 'A' || graph[x][y] == 'U' 
                    || graph[x][y] == 'D' || graph[x][y] == 'R' 
                    || graph[x][y] == 'L') 
                {
                    graph[nx][ny] = nextDirection(direction[2]);
                    if (nx == 0 || ny == 0 || nx == n-1 || ny == m-1) {
                        return {nx, ny};
                    }
                }
                queue.push({nx, ny});
            }
        }
    }
    return {-1, -1};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin>>n>>m;

    vector<vector<char>> graph(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin>>c;
            graph[i].push_back(c);
        }
    }
    queue<pair<int,int>> queue;
    pair<int, int> start;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (graph[i][j] == 'M') {
                queue.push({i, j});
            }
            if (graph[i][j] == 'A') {
                if (i == 0 || j == 0 || i == n-1 || j == m-1) {
                    cout<<"YES"<<endl<<0<<endl;
                    return 0;
                }
                start = make_pair(i, j);
            }
        }
    }
    queue.push(start);
    pair<int, int> escapeEnd = bfs(queue, graph);
    
    
    if (escapeEnd.first == -1) {
        cout<<"NO"<<endl;
        return 0;
    }


    string ans = "";
    
    int nx = escapeEnd.first;
    int ny = escapeEnd.second;

    while(nx != start.first || ny != start.second) {
        ans+=graph[nx][ny];
        if(graph[nx][ny] == 'U') {
          nx++;
        }
        else if(graph[nx][ny] =='D') {
          nx--;
        }
        else if(graph[nx][ny] == 'R') {
          ny--;
        }
        else if(graph[nx][ny] == 'L') {
          ny++;
        }
    }
    cout<<"YES"<<endl;
    cout<<ans.length()<<endl;
    reverse(ans.begin(),ans.end());
    cout<<ans<<endl;
    return 0;
}