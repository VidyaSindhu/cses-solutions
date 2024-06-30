#include <bits/stdc++.h>
using namespace std;

int l, timer = 1;
vector<vector<char>> graph;
int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

void dfs(int x, int y) {
  if (graph[x][y] != '.') return;
  graph[x][y] = '0';
  for (int i = 0; i < 4; i++) {
    int nx = x + directions[i][0];
    int ny = y + directions[i][1];
    if (nx >= 0 && nx < graph.size() && ny >= 0 && ny < graph[0].size()) {
      dfs(nx, ny);
    }
  }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int m, n;
    cin>>n>>m;

    for (int i = 0; i < n; i++){
        vector<char> temp(m);
        for (int j = 0; j < m; j++){
            cin>>temp[j];
        }
        graph.push_back(temp);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++){
        if (graph[i][j] == '.'){
          ans++;
          dfs(i, j);
        }
      }
    }

    cout<<ans<<endl;

    return 0;
}
