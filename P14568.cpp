#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 5010 + 10, mod = 998244353;
int n, a[MAXN], ans, dp[MAXN][MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    bool flag = false;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (a[i] == 3 && a[j] == 1) flag = true;
            if (a[i] == 2 && a[j] == 0) flag = true;
        }
    }
    if (flag) return cout << "0\n", 0;
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 1 || a[i] == 0)
            for (int j = 1; j <= n; j++) (dp[i][j] += dp[i - 1][j - 1]) %= mod;
        else {
            for (int j = n; ~j; j--) (dp[i - 1][j] += dp[i - 1][j + 1]) %= mod;
            for (int j = 0; j <= n; j++) (dp[i][j] += dp[i - 1][j]) %= mod;
        }
    }
    for (int i = 0; i <= n; i++) (ans += dp[n][i]) %= mod;
    cout << ans << '\n';

    return 0;
}