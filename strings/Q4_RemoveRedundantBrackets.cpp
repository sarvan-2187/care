#include <iostream>
#include <stack>
using namespace std;

string removeBrackets(string s) {
    string res;
    stack<char> st;

    for(char c : s) {
        if(c!='(' && c!=')')
            res += c;
    }

    return res;
}

int main() {
    cout << removeBrackets("A+(B+(C))");
}
