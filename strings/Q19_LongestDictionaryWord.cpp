#include <iostream>
#include <vector>
using namespace std;

bool isSub(string a,string b){
    int i=0,j=0;

    while(i<a.size() && j<b.size()){
        if(a[i]==b[j]) j++;
        i++;
    }

    return j==b.size();
}

int main(){
    string s="abpcplea";
    vector<string> d={"ale","apple","monkey","plea"};

    string ans="";

    for(string w:d){
        if(isSub(s,w)){
            if(w.size()>ans.size() || (w.size()==ans.size() && w<ans))
                ans=w;
        }
    }

    cout<<ans;
}
