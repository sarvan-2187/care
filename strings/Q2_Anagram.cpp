#include <iostream>
using namespace std;

bool isAnagram(string s1, string s2) {
    if(s1.length()!=s2.length()) return false;

    int freq[26]={0};

    for(char c:s1) freq[c-'a']++;
    for(char c:s2) freq[c-'a']--;

    for(int x:freq)
        if(x!=0) return false;

    return true;
}

int main() {
    cout << (isAnagram("geeks","kseeg") ? "true" : "false");
}
