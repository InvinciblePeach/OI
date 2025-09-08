#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 15, mod = 998244353;
int n, m, k, a[MAXN][MAXN], g[MAXN][1 << 10], h[MAXN][1 << 10], dp[2][1 << 10];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            static char c;
            cin >> c;
            a[i][j] = c - '0';
        }
    }
    for (int st = 0; st < (1 << n); st++)
        for (int i = 1; i <= n; i++)
            if (st >> (i - 1) & 1)
                for (int j = 1; j <= m; j++) g[a[i][j]][st] |= (1 << (j - 1));
    for (int st = 0; st < (1 << m); st++)
        for (int j = 1; j <= m; j++)
            if (st >> (j - 1) & 1)
                for (int i = 1; i <= n; i++) h[a[i][j]][st] |= (1 << (i - 1));
    dp[1][(1 << n) - 1] = 1;
    for (int nw = 1; nw <= k; nw++) {
        memset(dp[0], 0, sizeof(dp[0]));
        for (int i = 0; i < (1 << n); i++)
            for (int j = 1; j <= 9; j++) (dp[0][g[j][i]] += dp[1][i]) %= mod;
        memset(dp[1], 0, sizeof(dp[1]));
        for (int i = 0; i < (1 << m); i++)
            for (int j = 1; j <= 9; j++) (dp[1][h[j][i]] += dp[0][i]) %= mod;
    }
    int ans = 0;
    for (int i = 1; i < (1 << n); i++) (ans += dp[1][i]) %= mod;
    cout << ans << '\n';
    return 0;
}