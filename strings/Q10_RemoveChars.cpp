#include <iostream>
#include <unordered_set>
using namespace std;

int main(){
    string A="computer";
    string B="cat";

    unordered_set<char> st(B.begin(),B.end());

    string C="";

    for(char c:A)
        if(!st.count(c))
            C+=c;

    cout<<C;
}
