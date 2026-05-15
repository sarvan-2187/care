#include <iostream>
#include <vector>
using namespace std;

bool sorted(vector<int>& nums) {
    for(int i=1;i<nums.size();i++)
        if(nums[i] < nums[i-1]) return false;
    return true;
}

int main() {
    vector<int> nums = {5,2,3,1};
    int operations = 0;

    while(!sorted(nums)) {
        int minSum = 1e9, idx = 0;

        for(int i=0;i<nums.size()-1;i++) {
            if(nums[i] + nums[i+1] < minSum) {
                minSum = nums[i] + nums[i+1];
                idx = i;
            }
        }

        nums[idx] += nums[idx+1];
        nums.erase(nums.begin()+idx+1);

        operations++;
    }

    cout << operations;
    return 0;
}