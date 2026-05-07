#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> arr(n), even, odd;

    for(int i = 0; i < n; i++){
        cin >> arr[i];

        if(i % 2 == 0) even.push_back(arr[i]);
        else odd.push_back(arr[i]);
    }

    sort(even.begin(), even.end());
    sort(odd.rbegin(), odd.rend());

    for(int x : even) cout << x << " ";
    for(int x : odd) cout << x << " ";

    return 0;
}
