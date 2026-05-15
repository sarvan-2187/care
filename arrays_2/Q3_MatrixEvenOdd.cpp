#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int r, c;
    cin >> r >> c;

    vector<int> even, odd;

    for(int i=0;i<r;i++) {
        for(int j=0;j<c;j++) {
            int x; cin >> x;
            if((i*c+j)%2==0) even.push_back(x);
            else odd.push_back(x);
        }
    }

    sort(even.begin(), even.end());
    sort(odd.begin(), odd.end());

    cout << even[even.size()-2] + odd[odd.size()-2];
    return 0;
}