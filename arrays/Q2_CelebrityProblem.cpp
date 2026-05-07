#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> mat(n, vector<int>(n));

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> mat[i][j];

    int celeb = 0;

    for(int i = 1; i < n; i++){
        if(mat[celeb][i] == 1)
            celeb = i;
    }

    for(int i = 0; i < n; i++){
        if(i != celeb && (mat[celeb][i] == 1 || mat[i][celeb] == 0)){
            cout << -1;
            return 0;
        }
    }

    cout << celeb;
    return 0;
}



