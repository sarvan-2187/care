#include <bits/stdc++.h>
using namespace std;

bool cmp(pair<int,int> a, pair<int,int> b){
    if(a.second == b.second)
        return a.first < b.first;
    return a.second > b.second;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    unordered_map<int,int> freq;
    for(int i = 0; i < n; i++)
        cin >> arr[i];

    for(int i = 0; i < n; i++){
        freq[arr[i]]++;

        vector<pair<int,int>> temp;

        for(auto p : freq)
            temp.push_back(p);

        sort(temp.begin(), temp.end(), cmp);

        for(int j = 0; j < min(k, (int)temp.size()); j++)
            cout << temp[j].first << " ";

        cout << endl;
    }
    return 0;
}




