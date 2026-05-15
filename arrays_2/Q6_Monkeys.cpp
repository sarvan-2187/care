#include <iostream>
using namespace std;

int main() {
    int n,m,p,k,j;
    cin >> n >> m >> p >> k >> j;

    int monkeysDown = (m + k - 1)/k + (p + j - 1)/j;

    cout << max(0, n - monkeysDown);
    return 0;
}