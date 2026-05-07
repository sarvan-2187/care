#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);

    for(int i = 0; i < n; i++) cin >> arr[i];

    unordered_map<int,int> mp;
    mp[0] = -1;

    int sum = 0, ans = 0;

    for(int i = 0; i < n; i++){
        sum += (arr[i] == 0 ? -1 : 1);

        if(mp.count(sum))
            ans = max(ans, i - mp[sum]);
        else
            mp[sum] = i;
    }

    cout << ans;
    return 0;
}



