#include <iostream>
#include <cmath>
using namespace std;

int findCount(int arr[], int length, int num, int diff) {
    int count = 0;
    for(int i = 0; i < length; i++) {
        if(abs(arr[i] - num) <= diff)
            count++;
    }
    return count == 0 ? -1 : count;
}

int main() {
    int arr[] = {12, 3, 14, 56, 77, 13};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << findCount(arr, n, 13, 2);
    return 0;
}

