#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 25, mod = 998244353;
int n, m, ans, dp[1 << 20][MAXN], g[MAXN][MAXN];

int lowbit(int x) { return x & -x; }

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}

int inv(int x) { return qpow(x, mod - 2); }

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        g[u][v]++, g[v][u]++;
    }
    for (int i = 1; i <= n; i++) dp[1 << (i - 1)][i] = 1;
    for (int s = 1; s < (1 << n); s++) {
        for (int i = 1; i <= n; i++) {
            if (!dp[s][i]) continue;
            for (int v = 1; v <= n; v++) {
                if (!g[i][v]) continue;
                if (lowbit(s) > (1 << (v - 1))) continue;
                if (s & (1 << (v - 1))) {
                    if (lowbit(s) == (1 << (v - 1))) (ans += dp[s][i] * g[i][v]) %= mod;
                } else (dp[s | (1 << (v - 1))][v] += dp[s][i] * g[i][v]) %= mod;
            }
        }
    }
    cout << (ans - m + mod) % mod * inv(2) % mod << '\n';

    return 0;
}