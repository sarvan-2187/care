#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n), b(n-1);

    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n-1; i++) cin >> b[i];

    int low = 0, high = n - 2, ans = n - 1;

    while(low <= high){
        int mid = (low + high) / 2;

        if(a[mid] == b[mid])
            low = mid + 1;
        else{
            ans = mid;
            high = mid - 1;
        }
    }

    cout << ans;
    return 0;
}



