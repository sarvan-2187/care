#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, k;
    cin >> n;

    vector<int> arr(n);

    for(int i = 0; i < n; i++) cin >> arr[i];

    cin >> k;

    sort(arr.begin(), arr.end());

    cout << arr[k - 1];
    return 0;
}


