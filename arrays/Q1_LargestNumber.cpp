#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(string a, string b){
    return a + b > b + a;
}

int main() {
    int n;
    cin >> n;
    vector<string> arr(n);

    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        arr[i] = to_string(x);
    }

    sort(arr.begin(), arr.end(), cmp);

    if(arr[0] == "0"){
        cout << "0";
        return 0;
    }

    for(string s : arr) cout << s;
    return 0;
}



