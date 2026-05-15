#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {7,4,8,2,9};
    int count = 1, mx = arr[0];

    for(int i=1;i<arr.size();i++) {
        if(arr[i] > mx) {
            count++;
            mx = arr[i];
        }
    }

    cout << count;
    return 0;
}