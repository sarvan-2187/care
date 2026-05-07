#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int main() {
    int n, m;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    cin >> m;
    vector<int> b(m);
    unordered_set<int> s;

    for(int i = 0; i < m; i++){
        cin >> b[i];
        s.insert(b[i]);
    }

    for(int x : a){
        if(!s.count(x))
            cout << x << " ";
    }

    return 0;
}



