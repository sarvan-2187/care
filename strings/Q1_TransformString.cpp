#include <iostream>
#include <algorithm>
using namespace std;

int transform(string A, string B) {
    if(A.length() != B.length()) return -1;

    int freq[256] = {0};
    for(char c : A) freq[c]++;
    for(char c : B) freq[c]--;

    for(int i=0;i<256;i++)
        if(freq[i]) return -1;

    int i=A.length()-1, j=B.length()-1, ans=0;

    while(i>=0){
        if(A[i]==B[j]){
            i--; j--;
        } else {
            ans++;
            i--;
        }
    }
    return ans;
}

int main() {
    cout << transform("abd","bad");
}
