#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> arr = {0,-1,2,-3,1};
    sort(arr.begin(), arr.end());

    int n = arr.size();
    bool found = false;

    for(int i=0;i<n-2;i++) {
        int l=i+1, r=n-1;

        while(l<r) {
            int sum = arr[i] + arr[l] + arr[r];

            if(sum == 0) {
                found = true;
                break;
            }
            else if(sum < 0) l++;
            else r--;
        }
    }

    cout << (found ? "true" : "false");
    return 0;
}