#include <bits/stdc++.h>

using namespace std;

int n, a[305], sum[305], dp[305][305];

int main() {
    memset(dp, 0x7f, sizeof(dp));
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
        dp[i][i] = 0;
    }
    for (int len = 1; len < n; len ++) {
        for (int l = 1, r = l + len; r <= n; l ++, r ++) {
            int now_sum = sum[r] - sum[l - 1];
            for (int k = l; k < r; k ++) {
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r] + now_sum);
            }
        }
    }
    cout << dp[1][n] << endl;
    return 0;
}