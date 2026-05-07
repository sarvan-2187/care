#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arr(n), leftMax(n), rightMin(n);

    for(int i = 0; i < n; i++) cin >> arr[i];

    leftMax[0] = arr[0];
    for(int i = 1; i < n; i++)
        leftMax[i] = max(leftMax[i-1], arr[i]);

    rightMin[n-1] = arr[n-1];
    for(int i = n-2; i >= 0; i--)
        rightMin[i] = min(rightMin[i+1], arr[i]);

    for(int i = 0; i < n; i++){
        if(arr[i] >= leftMax[i] && arr[i] <= rightMin[i]){
            cout << arr[i];
            return 0;
        }
    }

    cout << -1;
    return 0;
}



