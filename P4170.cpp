#include <bits/stdc++.h>

using namespace std;

string s;
int n, dp[55][55];

int main() {
    memset(dp, 0x3f, sizeof(dp));

    cin >> s;
    n = s.size();
    s = ' ' + s;

    for (int i = 0; i <= n; i++) {
        dp[i][i] = 1;
    }

    for (int len = 1; len < n; len ++) {
        for (int i = 1; i <= n - len; i ++) {
            int j = i + len;
            if (s[i] == s[j]) {
                dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]);
            } else {
                for (int k = i; k < j; k ++) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
                }
            }
        }
    }

    cout << dp[1][n] << endl;
    return 0;
}