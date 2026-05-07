#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);

    for(int i = 0; i < n; i++) cin >> arr[i];

    vector<int> ans;
    int l = 0, r = n - 1;

    while(l <= r){
        if(l != r){
            ans.push_back(arr[r--]);
            ans.push_back(arr[l++]);
        } else {
            ans.push_back(arr[l++]);
        }
    }

    for(int x : ans) cout << x << " ";
    return 0;
}




