#include <bits/stdc++.h>
#define int long long
#define lc(p) (p << 1)
#define rc(p) (p << 1 | 1)

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e6 + 10;
int n, mod, dp[MAXN], siz[MAXN], frac[MAXN];

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        b >>= 1, (a *= a) %= mod;
    }
    return res;
}

int inv(int x) { return qpow(x, mod - 2); }

int C(int a, int b) { return frac[a] * inv(frac[b]) % mod * inv(frac[a - b]) % mod; }

int lucas(int a, int b) {
    if (!b) return 1;
    return C(a % mod, b % mod) * lucas(a / mod, b / mod) % mod;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> mod;
    frac[0] = 1;
    for (int i = 1; i <= n; i++) frac[i] = i * frac[i - 1] % mod;
    for (int i = n; i; i--) {
        dp[i] = siz[i] = 1;
        if (lc(i) <= n) siz[i] += siz[lc(i)];
        if (rc(i) <= n) siz[i] += siz[rc(i)];
        if (lc(i) <= n) (dp[i] *= lucas(siz[i] - 1, siz[lc(i)]) * dp[lc(i)] % mod) %= mod;
        if (rc(i) <= n) (dp[i] *= dp[rc(i)]) %= mod;
    }
    cout << dp[1] << '\n';

    return 0;
}