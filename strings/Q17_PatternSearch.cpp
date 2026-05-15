#include <iostream>
using namespace std;

int main(){
    string txt="GeeksForGeeks";
    string pat="For";

    for(int i=0;i<=txt.size()-pat.size();i++){
        int j;

        for(j=0;j<pat.size();j++){
            if(txt[i+j]!=pat[j])
                break;
        }

        if(j==pat.size()){
            cout<<i;
            return 0;
        }
    }

    cout<<-1;
}
