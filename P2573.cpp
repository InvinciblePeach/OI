#include <bits/stdc++.h>

using namespace std;

const int mod = 10000;
int n, k, dp[1005][1005];

int main() {
    cin >> n >> k;

    dp[1][0] = 1;

    for (int i = 2; i <= n; i ++) {
        int sum = 0;
        for (int j = 0; j <= k; j ++) {
            sum += dp[i - 1][j];
            sum %= mod;
            dp[i][j] = sum;
            if (j - i + 1 >= 0) {
                sum -= dp[i - 1][j - i + 1];
                sum += mod;
                sum %= mod;
            }
        }
    }

    cout << dp[n][k] % mod << endl;

    return 0;
}