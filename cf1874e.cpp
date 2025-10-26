#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 210, MAXM = 2.2e5 + 10, mod = 1e9 + 7;
int n, m, lim, dp[MAXN], C[MAXN][MAXN], f[MAXM], pw[MAXM][MAXN];
int ans[MAXM], ogf[MAXM], Ogf[MAXM];

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        if (b >>= 1) (a *= a) %= mod;
    }
    return res;
}

int inv(int x) { return qpow(x, mod - 2); }

void solve() {
    ogf[0] = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = m; j; j--) ogf[j] = (ogf[j] * -i + ogf[j - 1]) % mod;
        ogf[0] = ogf[0] * -i % mod;
    }
    for (int i = 1; i <= m; i++) {
        int mul = f[i], div = 1;
        for (int j = 1; j <= m; j++)
            if (i ^ j) (div *= (i - j)) %= mod;
        (mul *= inv(div)) %= mod;
        int q = inv(i);
        Ogf[0] = ogf[0] * -q % mod;
        for (int j = 1; j <= m; j++) Ogf[j] = (ogf[j] - Ogf[j - 1]) * -q % mod;
        for (int j = 0; j <= m; j++) (ans[j] += mul * Ogf[j]) %= mod;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> lim;
    m = (n * (n + 1) >> 1) + 1;
    if (lim >= m) return cout << 0, 0;
    if (n == 1) {
        if (lim == 1) return cout << 1, 0;
        return cout << 0, 0;
    }
    C[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }
    for (int i = 1; i <= m; i++) {
        pw[i][0] = 1;
        for (int j = 1; j <= n; j++) pw[i][j] = pw[i][j - 1] * i % mod;
    }
    for (int x = 1; x <= m; x++) {
        dp[0] = 1;
        for (int k = 1; k <= n; k++) {
            dp[k] = 0;
            for (int i = 1; i <= k; i++) (dp[k] += dp[i - 1] * dp[k - i] % mod * C[k - 1][i - 1]) %= mod;
            (dp[k] *= pw[x][k]) %= mod;
        }
        f[x] = dp[n];
    }
    solve();
    int res = 0;
    for (int i = lim; i <= m; i++) (res += ans[i]) %= mod;
    cout << (res + mod) % mod << '\n';

    return 0;
}