#include <iostream>
using namespace std;

int main(){
    string s="(())))((";

    int open=0;

    for(char c:s)
        if(c=='(') open++;

    int close=0;

    for(int i=0;i<s.size();i++){
        if(s[i]=='(') open--;
        else close++;

        if(open==close){
            cout<<i+1;
            return 0;
        }
    }

    cout<<s.size();
}
