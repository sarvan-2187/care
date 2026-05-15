#include <iostream>
using namespace std;

long long fact(int n){
    long long f=1;
    for(int i=2;i<=n;i++) f*=i;
    return f;
}

long long ways(int r,int g,int b){
    return fact(r+g+b)/(fact(r)*fact(g)*fact(b));
}

int main(){
    int n=4,r=1,g=1,b=1;
    long long ans=0;

    for(int i=r;i<=n;i++){
        for(int j=g;j<=n-i;j++){
            int k=n-i-j;
            if(k>=b)
                ans += ways(i,j,k);
        }
    }

    cout<<ans;
}
