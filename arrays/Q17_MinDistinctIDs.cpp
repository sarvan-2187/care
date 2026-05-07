#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    cin >> n;

    vector<int> arr(n);

    for(int i = 0; i < n; i++) cin >> arr[i];

    cin >> m;

    unordered_map<int,int> freq;

    for(int x : arr) freq[x]++;

    vector<int> counts;
    for(auto p : freq)
        counts.push_back(p.second);

    sort(counts.begin(), counts.end());
    int distinct = counts.size();
    for(int x : counts){
        if(m >= x){
            m -= x;
            distinct--;
        }
    }
    cout << distinct;
    return 0;
}



