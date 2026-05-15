#include <iostream>
#include <vector>
using namespace std;

int firstOcc(vector<int>& arr, int x) {
    int l=0,r=arr.size()-1,ans=-1;
    while(l<=r){
        int mid=(l+r)/2;
        if(arr[mid]==x){
            ans=mid;
            r=mid-1;
        }
        else if(arr[mid]<x) l=mid+1;
        else r=mid-1;
    }
    return ans;
}

int lastOcc(vector<int>& arr, int x) {
    int l=0,r=arr.size()-1,ans=-1;
    while(l<=r){
        int mid=(l+r)/2;
        if(arr[mid]==x){
            ans=mid;
            l=mid+1;
        }
        else if(arr[mid]<x) l=mid+1;
        else r=mid-1;
    }
    return ans;
}

int main() {
    vector<int> arr = {1,3,5,5,5,5,67,123,125};
    int x = 5;
    cout << firstOcc(arr,x) << " " << lastOcc(arr,x);
    return 0;
}


