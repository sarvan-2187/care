#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    string s="i.like.this.program.very.much";

    vector<string> words;
    string temp="";

    for(char c:s){
        if(c=='.'){
            if(!temp.empty()){
                words.push_back(temp);
                temp="";
            }
        } else temp+=c;
    }

    if(!temp.empty()) words.push_back(temp);

    reverse(words.begin(),words.end());

    for(int i=0;i<words.size();i++){
        cout<<words[i];
        if(i!=words.size()-1) cout<<".";
    }
}
