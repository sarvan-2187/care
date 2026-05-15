#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    vector<char> arr = {'r','g','b','g','b','b','r'};
    unordered_map<char,int> freq;

    for(char c : arr) freq[c]++;

    for(char c : arr) {
        if(freq[c] % 2 != 0) {
            cout << c;
            return 0;
        }
    }

    cout << "All are even";
    return 0;
}


