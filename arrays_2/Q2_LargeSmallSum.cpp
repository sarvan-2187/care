#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int LargeSmallSum(vector<int>& arr) {
    int n = arr.size();
    if(n <= 3) return 0;

    vector<int> evenPos, oddPos;

    for(int i = 0; i < n; i++) {
        if(i % 2 == 0) evenPos.push_back(arr[i]);
        else oddPos.push_back(arr[i]);
    }

    sort(evenPos.begin(), evenPos.end());
    sort(oddPos.begin(), oddPos.end());

    return evenPos[evenPos.size()-2] + oddPos[1];
}

int main() {
    vector<int> arr = {3,2,1,7,5,4};
    cout << LargeSmallSum(arr);
    return 0;
}


