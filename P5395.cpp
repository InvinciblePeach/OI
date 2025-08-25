#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 8e5 + 10, mod = 167772161, g = 3;
int n, len = 1, d, a[MAXN], b[MAXN], rev[MAXN];
int frac[MAXN], invf[MAXN];

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
    for (int i = 0; i < len; i++)
        if (i > rev[i]) swap(a[i], a[rev[i]]);
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

    cin >> n;

    frac[0] = 1;
    for (int i = 1; i <= n; i++) frac[i] = frac[i - 1] * i % mod;
    invf[n] = inv(frac[n]);
    for (int i = n - 1; ~i; i--) invf[i] = invf[i + 1] * (i + 1) % mod;
    for (int i = 0; i <= n; i++)
        a[i] = (i & 1 ? (mod - invf[i]) : invf[i]), b[i] = qpow(i, n) * invf[i] % mod;

    while (len <= (n << 1)) len <<= 1, d++;
    for (int i = 0; i < len; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (d - 1));
    ntt(a, 1), ntt(b, 1);
    for (int i = 0; i < len; i++) (a[i] *= b[i]) %= mod;
    ntt(a, -1);
    int tmp = inv(len);
    for (int i = 0; i <= n; i++)
        cout << a[i] * tmp % mod << " \n"[i == n];

    return 0;
}  