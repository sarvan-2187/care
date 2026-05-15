#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void dfs(int i,int j,vector<vector<int>>& grid,vector<vector<int>>& vis,int& cnt){
    int n=grid.size(),m=grid[0].size();
    if(i<0||j<0||i>=n||j>=m||vis[i][j]||grid[i][j]==0) return;

    vis[i][j]=1;
    cnt++;

    dfs(i+1,j,grid,vis,cnt);
    dfs(i-1,j,grid,vis,cnt);
    dfs(i,j+1,grid,vis,cnt);
    dfs(i,j-1,grid,vis,cnt);
}

int main(){
    int n,m;
    cin>>n>>m;

    vector<vector<int>> grid(n,vector<int>(m));
    vector<vector<int>> vis(n,vector<int>(m,0));

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin>>grid[i][j];

    vector<int> groups;

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(grid[i][j]==1 && !vis[i][j]){
                int cnt=0;
                dfs(i,j,grid,vis,cnt);
                groups.push_back(cnt);
            }
        }
    }

    sort(groups.rbegin(), groups.rend());

    int suresh = 0;
    for(int i=1;i<groups.size();i+=2)
        suresh += groups[i];

    cout << suresh;
    return 0;
}


