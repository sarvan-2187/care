#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main() {
    vector<int> arr = {60,20,50,40,10,50,60};
    stack<int> st;
    int maxArea = 0, n = arr.size();
    for(int i=0;i<=n;i++) {
        int h = (i == n) ? 0 : arr[i];
        while(!st.empty() && h < arr[st.top()]) {
            int height = arr[st.top()];
            st.pop();
            int width = st.empty() ? i : i - st.top() - 1;
            maxArea = max(maxArea, height * width);
        }
        st.push(i);
    }
    cout << maxArea;
    return 0;
}

