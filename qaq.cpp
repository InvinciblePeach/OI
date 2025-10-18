#include <bits/stdc++.h>
#define int long long

using namespace std;

const int mod = 998244353;
int n, m, k;
int dp[1005][1005];

signed main() {
    cin >> n >> m >> k;

    dp[1][0] = m;

    for (int i = 2; i <= n; i++) {
        dp[i][0] = m;
        for (int j = 1; j <= k; j++) {
            dp[i][j] = (dp[i - 1][j - 1] * (m - 1) + dp[i - 1][j]) % mod;
        }
    }
    cout << dp[n][k] << endl;
    return 0;
}