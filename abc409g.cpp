#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 4e5 + 10, mod = 998244353, g = 3;
int n, len = 1, d, p, np, f[MAXN], frac[MAXN], a[MAXN], b[MAXN];
int rev[MAXN], ans[MAXN];

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}

int inv(int a) { return qpow(a, mod - 2); }

const int ginv = inv(g);

void ntt(int *a, int type) {
    for (int i = 1; i < len; i++)
        if (rev[i] > i) swap(a[i], a[rev[i]]);
    for (int mid = 1; mid < len; mid <<= 1) {
        int gn = qpow(type > 0 ? g : ginv, (mod - 1) / (mid << 1));
        for (int L = mid << 1, j = 0; j < len; j += L) {
            int G = 1;
            for (int k = 0; k < mid; k++, (G *= gn) %= mod) {
                int p = a[j + k], q = G * a[j + k + mid] % mod;
                a[j + k] = (p + q) % mod, a[j + k + mid] = (p - q + mod) % mod;
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> p;
    (p *= inv(100)) %= mod, np = (1 - p + mod) % mod;
    b[0] = f[0] = frac[0] = 1;
    for (int i = 1; i <= n - 2; i++) {
        b[i] = b[i - 1] * np % mod * inv(i) % mod;
        f[i] = f[i - 1] * (n - i + np) % mod * inv(n - i) % mod;
        frac[i] = frac[i - 1] * i % mod;
    }
    for (int i = 0; i <= n - 2; i++)
        a[i] = f[i] * frac[n - i - 2] % mod;
    while (len <= 2 * n) len <<= 1, d++;
    for (int i = 0; i < len; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (d - 1));
    ntt(a, 1), ntt(b, 1);
    for (int i = 0; i < len; i++) (a[i] *= b[i]) %= mod;
    ntt(a, -1);
    ans[1] = n;
    int tmp = inv(len);
    for (int i = 2; i <= n; i++) {
        ans[i] = qpow(p, i - 1) * inv(frac[i - 2]) % mod * (a[n - i] * tmp % mod) % mod;
        ans[1] = (ans[1] - ans[i] + mod) % mod;
    }
    for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];

    return 0;
}