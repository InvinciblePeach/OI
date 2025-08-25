#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 60, mod = 1e9 + 7;
int T, n, m, k, ans, a[MAXN], frac[MAXN], invf[MAXN], pre[MAXN], suf[MAXN], y[MAXN];

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

int calc(int x) {
    x %= mod;
    pre[0] = x, suf[k + 2] = 1;
    for (int i = 1; i <= k + 1; i++) pre[i] = pre[i - 1] * (x - i) % mod;
    for (int i = k + 1; ~i; i--) suf[i] = suf[i + 1] * (x - i) % mod;
    
    int res = 0;
    for (int i = 1; i <= k + 1; i++)
        (res += y[i] * pre[i - 1] % mod * suf[i + 1] % mod * invf[i] % mod * invf[k + 1 - i] % mod * ((k + 1 - i) & 1) ? -1 : 1) %= mod;
    cerr << res << '\n';
    return (res + mod) % mod;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    frac[0] = 1;
    for (int i = 1; i < MAXN; i++) frac[i] = frac[i - 1] * i % mod;
    invf[MAXN - 1] = inv(frac[MAXN - 1]);
    for (int i = MAXN - 2; ~i; i--) invf[i] = invf[i + 1] * (i + 1) % mod;
    cin >> T;
    while (T --> 0) {
        ans = 0;
        cin >> n >> m;
        for (int i = 1; i <= m; i++) cin >> a[i];
        sort(a + 1, a + 1 + m);
        k = m + 1;
        for (int i = 1; i <= k + 1; i++) y[i] = (y[i - 1] + qpow(i, k)) % mod;
        for (int i = 0; i <= m; i++) {
            (ans += calc(n - a[i])) %= mod;
            for (int j = i + 1; j <= m; j++) (ans -= qpow(a[j] - a[i], k)) %= mod;
        }
        cout << (ans + mod) % mod << '\n';
    }

    return 0;
}