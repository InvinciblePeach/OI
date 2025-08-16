#include <bits/stdc++.h>

using namespace std;

int n, k, dp[205][20005];
const int mod = 504;

int main() {
    cin >> n >> k;

    if (k == 0) {
        cout << 1 << endl;
        return 0;
    }
    if (k >= 2 * n + 1) {
        cout << 0 << endl;
        return 0;
    }

    for (int i = 0; i <= 2 * n - 1; i++) {
        dp[i][0] = 1;
    }

    for (int i = 1; i <= 2 * n - 1; i++) {
    }

    return 0;
}