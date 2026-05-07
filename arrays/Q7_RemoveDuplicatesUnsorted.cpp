#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    unordered_set<int> seen;

    for(int i = 0; i < n; i++) cin >> arr[i];

    for(int x : arr){
        if(!seen.count(x)){
            cout << x << " ";
            seen.insert(x);
        }
    }

    return 0;
}



