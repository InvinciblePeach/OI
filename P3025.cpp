#include <bits/stdc++.h>

using namespace std;

const int mod = 19650827;
int n;
int h[1005], dp[1005][1005][2] = {0};

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    for (int i = 0; i <= n; i++) {
        dp[i][i][0] = 1;
    }

    for (int len = 1; len <= n; len++) {
        for (int i = 1; i + len <= n; i++) {
            int j = i + len;
            if (h[i] < h[i + 1]) {
                dp[i][j][0] += dp[i + 1][j][0];
            }
            if (h[i] < h[j]) {
                dp[i][j][0] += dp[i + 1][j][1];
                dp[i][j][1] += dp[i][j - 1][0];
            }
            if (h[j] > h[j - 1]) {
                dp[i][j][1] += dp[i][j - 1][1];
            }
            dp[i][j][0] %= mod;
            dp[i][j][1] %= mod;
        }
    }

    cout << (dp[1][n][0] + dp[1][n][1]) % mod << endl;

    return 0;
}