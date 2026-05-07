#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> arr(n), freq(n + 1, 0);

    for(int i = 0; i < n; i++){
        cin >> arr[i];
        freq[arr[i]]++;
    }

    for(int i = 1; i <= n; i++)
        cout << freq[i] << " ";

    return 0;
}
