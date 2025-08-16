#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 2010, mod = 1e9 + 7;
int n, ans, dp[MAXN][MAXN], sum[MAXN][MAXN];

signed main() {
    freopen("moon.in", "r", stdin);
    freopen("moon.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    sum[0][0] = dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            dp[i][j] = (sum[i - 1][j - 1] - (j - i - 1 > 0 ? sum[i - 1][j - i - 1] : 0)) % mod;
            sum[i][j] = (sum[i][j - 1] + dp[i][j]) % mod;
        }
    }
    for (int i = 1; i <= n; i++)
        (ans += dp[i][n]) %= mod;
    cout << ans << '\n';
    return 0;
}