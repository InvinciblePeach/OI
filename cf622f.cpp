#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 1e6 + 10, mod = 1e9 + 7;
int n, k, ans, invf[MAXN], frac[MAXN], pre[MAXN], suf[MAXN], x[MAXN], y[MAXN];

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

    cin >> n >> k;
    k++, y[0] = 0;
    for (int i = 1; i <= k; i++) y[i] = (y[i - 1] + qpow(i, k - 1)) % mod;

    frac[0] = suf[k + 1] = 1, pre[0] = n;
    for (int i = 1; i <= k; i++) pre[i] = pre[i - 1] * (n - i) % mod;
    for (int i = k; ~i; i--) suf[i] = suf[i + 1] * (n - i) % mod;
    for (int i = 1; i <= k; i++) frac[i] = frac[i - 1] * i % mod;
    invf[k] = inv(frac[k]);
    for (int i = k - 1; ~i; i--) invf[i] = invf[i + 1] * (i + 1) % mod;

    ans = y[0] * suf[1] % mod * invf[k] % mod * ((k & 1) ? mod - 1 : 1) % mod;
    for (int i = 1; i <= k; i++)
        (ans += y[i] * pre[i - 1] % mod * suf[i + 1] % mod * invf[i] % mod * invf[k - i] % mod * (((k - i) & 1) ? -1 : 1) % mod) %= mod;
    cout << (ans + mod) % mod << '\n';

    return 0;
}