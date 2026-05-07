#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arr(n), left(n), right(n);

    for(int i = 0; i < n; i++) cin >> arr[i];

    left[0] = arr[0];
    for(int i = 1; i < n; i++)
        left[i] = max(left[i-1], arr[i]);

    right[n-1] = arr[n-1];
    for(int i = n-2; i >= 0; i--)
        right[i] = min(right[i+1], arr[i]);

    for(int i = 0; i < n; i++){
        if(arr[i] >= left[i] && arr[i] <= right[i]){
            cout << arr[i];
            return 0;
        }
    }

    cout << -1;
    return 0;
}



