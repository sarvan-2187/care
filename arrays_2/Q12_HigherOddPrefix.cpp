#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n), b(n);

    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<n;i++) cin >> b[i];

    int s1=0, s2=0;

    for(int i=0;i<n;i++) {
        if(a[i]%2) s1 += a[i];
        if(b[i]%2) s2 += b[i];

        cout << max(s1,s2) << " ";
    }

    return 0;
}