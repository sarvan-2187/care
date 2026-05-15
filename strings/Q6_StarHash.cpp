#include <iostream>
using namespace std;

int main() {
    string s="##***#";

    int star=0, hash=0;

    for(char c:s){
        if(c=='*') star++;
        else if(c=='#') hash++;
    }

    cout << star-hash;
}
