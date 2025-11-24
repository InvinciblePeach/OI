#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 110, MAXM = 2010, mod = 998244353;
int n, m, ans, a[MAXN][MAXM], sum[MAXN], f[MAXN][MAXN << 1], g[MAXN][MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> a[i][j], (sum[i] += a[i][j]) %= mod;

    for (int k = 1; k <= m; k++) {
        memset(f, 0, sizeof(f));
        f[0][n] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = n - i; j <= n + i; j++)
                f[i][j] =
                    (f[i - 1][j] + a[i][k] * f[i - 1][j - 1] % mod + (sum[i] - a[i][k]) * f[i - 1][j + 1] % mod) % mod;
        for (int i = 1; i <= n; i++) (ans -= f[n][n + i]) %= mod;
    }
    g[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= i; j++) g[i][j] = (g[i - 1][j] + (j > 0 ? sum[i] * g[i - 1][j - 1] % mod : 0)) % mod;
    for (int i = 1; i <= n; i++) (ans += g[n][i]) %= mod;
    cout << (ans + mod) % mod << '\n';

    return 0;
}