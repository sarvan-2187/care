#include <iostream>
#include <vector>
using namespace std;

int main() {
    int R,C;
    cin>>R>>C;

    vector<vector<int>> mat(R, vector<int>(C));

    for(int i=0;i<R;i++)
        for(int j=0;j<C;j++)
            cin>>mat[i][j];

    vector<int> rowKeep(R), colKeep(C);

    for(int i=0;i<R;i++) {
        int mn=0;
        for(int j=1;j<C;j++)
            if(mat[i][j] < mat[i][mn]) mn=j;
        rowKeep[i]=mn;
    }

    for(int j=0;j<C;j++) {
        int mn=0;
        for(int i=1;i<R;i++)
            if(mat[i][j] < mat[mn][j]) mn=i;
        colKeep[j]=mn;
    }

    for(int i=0;i<R;i++) {
        for(int j=0;j<C;j++) {
            if(j!=rowKeep[i] && i!=colKeep[j])
                cout<<mat[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}