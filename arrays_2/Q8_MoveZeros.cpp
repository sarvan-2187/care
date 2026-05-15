#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {4,5,0,1,9,0,5,0};
    int idx = 0;

    for(int i=0;i<arr.size();i++) {
        if(arr[i] != 0)
            arr[idx++] = arr[i];
    }

    while(idx < arr.size())
        arr[idx++] = 0;

    for(int x : arr) cout << x << " ";
    return 0;
}