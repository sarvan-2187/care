#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    vector<int> arr = {1,4,45,6,0,19};
    int x = 51;

    int n = arr.size();
    int sum = 0, start = 0, ans = INT_MAX;

    for(int end=0; end<n; end++) {
        sum += arr[end];

        while(sum > x) {
            ans = min(ans, end-start+1);
            sum -= arr[start++];
        }
    }

    cout << (ans == INT_MAX ? 0 : ans);
    return 0;
}