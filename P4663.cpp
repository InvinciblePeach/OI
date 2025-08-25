#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 1010;
int k, n, mod, ans, dp[MAXN][MAXN], y[MAXN], pre[MAXN], suf[MAXN], frac[MAXN], invf[MAXN];

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

    cin >> k >> n >> mod;
    frac[0] = 1;
    for (int i = 1; i <= (n << 1); i++) frac[i] = frac[i - 1] * i % mod;
    invf[n << 1] = inv(frac[n << 1]);
    for (int i = (n << 1) - 1; ~i; i--) invf[i] = invf[i + 1] * (i + 1) % mod;

    for (int j = 0; j <= (n << 1 | 1); j++) dp[0][j] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= (n << 1 | 1); j++)
            dp[i][j] = (dp[i - 1][j - 1] * j % mod + dp[i][j - 1]) % mod;
    }

    pre[0] = --k, suf[n << 1 | 1] = 1;
    for (int i = 0; i <= (n << 1); i++) y[i] = dp[n][i + 1];
    for (int i = 1; i <= (n << 1); i++) pre[i] = pre[i - 1] * (k - i) % mod;
    for (int i = (n << 1); ~i; i--) suf[i] = suf[i + 1] * (k - i) % mod;

    ans = y[0] * suf[1] % mod * invf[n << 1] % mod;
    for (int i = 1; i <= (n << 1); i++)
        (ans += y[i] * pre[i - 1] % mod * suf[i + 1] % mod * invf[i] % mod * invf[(n << 1) - i] % mod * (i & 1 ? -1 : 1)) %= mod;
    (ans += mod) %= mod;
    cout << (frac[n] * ans) % mod;

    return 0;
}