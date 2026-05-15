#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main(){
    vector<string> stops={"TH","GA","IC","HA","TE","LU","NI","CA"};
    vector<int> path={800,600,750,900,1400,1200,1100,1500};

    string src="TH", dest="HA";

    int s=-1,d=-1;

    for(int i=0;i<stops.size();i++){
        if(stops[i]==src) s=i;
        if(stops[i]==dest) d=i;
    }

    int dist=0;
    int i=s;

    while(i!=d){
        dist+=path[i];
        i=(i+1)%stops.size();
    }

    cout<<ceil(dist/200.0);
}
