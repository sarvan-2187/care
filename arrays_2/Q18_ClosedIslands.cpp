#include <iostream>
#include <vector>
using namespace std;

void dfs(int i,int j,vector<vector<int>>& mat,vector<vector<int>>& vis,bool &closed){
    int n=mat.size(),m=mat[0].size();

    if(i<0||j<0||i>=n||j>=m) return;
    if(vis[i][j] || mat[i][j]==0) return;

    if(i==0 || j==0 || i==n-1 || j==m-1)
        closed = false;

    vis[i][j]=1;

    dfs(i+1,j,mat,vis,closed);
    dfs(i-1,j,mat,vis,closed);
    dfs(i,j+1,mat,vis,closed);
    dfs(i,j-1,mat,vis,closed);
}

int main(){
    int n=5,m=8;
    vector<vector<int>> mat = {
        {0,0,0,0,0,0,0,1},
        {0,1,1,1,1,0,0,1},
        {0,1,0,1,0,0,0,1},
        {0,1,1,1,1,0,1,0},
        {1,0,0,0,0,1,0,1}
    };
    vector<vector<int>> vis(n, vector<int>(m,0));
    int count = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(mat[i][j]==1 && !vis[i][j]){
                bool closed = true;
                dfs(i,j,mat,vis,closed);
                if(closed) count++;
            }
        }
    }
    cout << count;
    return 0;
}


