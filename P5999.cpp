#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 2010, mod = 1e9 + 7;
int n, s, t, dp[MAXN][MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> s >> t;
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            if ((i ^ s) && (i ^ t))
                dp[i][j] = (j * dp[i - 1][j + 1] % mod + (j - (i > s) - (i > t)) * dp[i - 1][j - 1] % mod) % mod;
            else
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % mod;
        }
    }
    cout << dp[n][1] << '\n';

    return 0;
}