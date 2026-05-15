#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

int main() {
    vector<int> arr = {5,15,1,3,2,8};
    priority_queue<int> leftHeap;
    priority_queue<int, vector<int>, greater<int>> rightHeap;
    for(int x : arr) {
        if(leftHeap.empty() || x <= leftHeap.top())
            leftHeap.push(x);
        else
            rightHeap.push(x);

        if(leftHeap.size() > rightHeap.size() + 1) {
            rightHeap.push(leftHeap.top());
            leftHeap.pop();
        }
        else if(rightHeap.size() > leftHeap.size()) {
            leftHeap.push(rightHeap.top());
            rightHeap.pop();
        }

        double median;

        if(leftHeap.size() == rightHeap.size())
            median = (leftHeap.top() + rightHeap.top()) / 2.0;
        else
            median = leftHeap.top();

        cout << fixed << setprecision(1) << median << " ";
    }
    return 0;
}


