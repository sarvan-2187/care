#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {0,1,0,1,1};

    int north = 0, crossings = 0;

    for(int x : arr) {
        if(x == 0) north++;
        else crossings += north;
    }

    cout << crossings;
    return 0;
}