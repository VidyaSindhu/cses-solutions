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

void bfs(int x, int y, vector<vector<char>>&graph){
    queue<pair<int,int>> q;
    int i,nx=0,ny=0;
    int n=graph.size();
    int m=graph[0].size();
    q.push({x,y});
    vector<vector<char>> path(n, vector<char>(m));
    bool found=false;
    while(!q.empty()){
        pair<int,int> curr = q.front();
        q.pop();
        for(i=0;i<4;i++)
        {
            nx = curr.first + directions[i][0];
            ny = curr.second + directions[i][1];
            if((nx >= 0 && nx < n && ny >= 0 && ny < m) && (graph[nx][ny]=='.' || graph[nx][ny]=='B')) {
                path[nx][ny]=nextDirection(directions[i][2]);
                
                if( graph[nx][ny]=='B')
                {
                    found=true;
                    break;
                }
                graph[nx][ny] = '#';
                q.push(make_pair(nx, ny));
            }
        }
        if(found == true)
        break;
    }
    
    if(found==false){
        cout<<"NO"<<endl;
        return;
    }
    
    string ans="";
    while(!(nx==x && ny==y)) {
        ans+=path[nx][ny];
        if(path[nx][ny] == 'U') {
          nx++;
        }
        else if(path[nx][ny] =='D') {
          nx--;
        }
        else if(path[nx][ny] == 'R') {
          ny--;
        }
        else if(path[nx][ny] == 'L') {
          ny++;
        }
        
    }
    cout<<"YES"<<endl;
    cout<<ans.length()<<endl;
    reverse(ans.begin(),ans.end());
    cout<<ans<<endl;
}

int main() {
    int n, m,i,j;
    cin >> n >> m;
    vector<vector<char>> graph(n, vector<char>(m));

    for(i=0;i<n;i++){
        for(j=0;j<m;j++)
        cin>>graph[i][j];
    }
    
    for(i=0;i<n;i++){
        for(j=0;j<m;j++) {
            if(graph[i][j]=='A')
            {
                bfs(i,j,graph);
            }
        }
   } 
}
