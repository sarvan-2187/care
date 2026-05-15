#include <iostream>
#include <vector>
using namespace std;

const long long MOD=1000000007;

int main(){
    int N=2,K=0;

    vector<vector<long long>> dp(N+1, vector<long long>(K+1,0));
    dp[0][0]=1;

    for(int i=1;i<=N;i++){
        dp[i][0]=0;
        long long sum=0;

        for(int j=0;j<=K;j++)
            sum=(sum+dp[i-1][j])%MOD;

        dp[i][0]=(sum*21)%MOD;

        for(int j=1;j<=K;j++)
            dp[i][j]=(dp[i-1][j-1]*5)%MOD;
    }

    long long ans=0;
    for(int j=0;j<=K;j++)
        ans=(ans+dp[N][j])%MOD;

    cout<<ans;
}
