#include <iostream>
#include <vector>
using namespace std;

int main(){
    string s1="11", s2="23";

    int n=s1.size(), m=s2.size();

    vector<int> res(n+m,0);

    for(int i=n-1;i>=0;i--){
        for(int j=m-1;j>=0;j--){
            int mul=(s1[i]-'0')*(s2[j]-'0');
            int sum=mul+res[i+j+1];

            res[i+j]+=sum/10;
            res[i+j+1]=sum%10;
        }
    }

    string ans="";
    for(int x:res)
        if(!(ans.empty() && x==0))
            ans+=to_string(x);

    cout<<(ans.empty()?"0":ans);
}
