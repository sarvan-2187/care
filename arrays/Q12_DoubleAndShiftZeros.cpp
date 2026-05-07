#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);

    for(int i = 0; i < n; i++) cin >> arr[i];

    for(int i = 0; i < n-1; i++){
        if(arr[i] != 0 && arr[i] == arr[i+1]){
            arr[i] *= 2;
            arr[i+1] = 0;
        }
    }

    vector<int> ans;

    for(int x : arr)
        if(x != 0) ans.push_back(x);

    while(ans.size() < n)
        ans.push_back(0);

    for(int x : ans) cout << x << " ";

    return 0;
}



