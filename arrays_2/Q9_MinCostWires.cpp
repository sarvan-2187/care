#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {4,3,2,6};

    priority_queue<int, vector<int>, greater<int>> pq(arr.begin(), arr.end());

    int cost = 0;

    while(pq.size() > 1) {
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();

        int sum = a + b;
        cost += sum;

        pq.push(sum);
    }

    cout << cost;
    return 0;
}