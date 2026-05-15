#include <iostream>
#include <climits>
using namespace std;

int main(){
    string s="timetopractice";
    string p="toc";

    int need[256]={0}, have[256]={0};

    for(char c:p) need[c]++;

    int count=0,start=0,minLen=INT_MAX,begin=0;

    for(int end=0;end<s.size();end++){
        have[s[end]]++;

        if(have[s[end]]<=need[s[end]])
            count++;

        while(count==p.size()){
            if(end-start+1<minLen){
                minLen=end-start+1;
                begin=start;
            }

            have[s[start]]--;

            if(have[s[start]]<need[s[start]])
                count--;

            start++;
        }
    }

    if(minLen==INT_MAX) cout<<"";
    else cout<<s.substr(begin,minLen);
}
