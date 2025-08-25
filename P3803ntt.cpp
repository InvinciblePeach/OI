#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 1e6 + 10, mod = 998244353, g = 3, ginv = 332748118;
int n, m, d, len = 1, a[MAXN], b[MAXN], rev[MAXN];

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

    cin >> n >> m;
    for (int i = 0; i <= n; i++) cin >> a[i];
    for (int i = 0; i <= m; i++) cin >> b[i];
    while (len <= n + m) len <<= 1, d++;
    for (int i = 0; i < len; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (d - 1));
    ntt(a, 1), ntt(b, 1);
    for (int i = 0; i < len; i++) (a[i] *= b[i]) %= mod;
    ntt(a, -1);
    int tmp = inv(len);
    for (int i = 0; i <= n + m; i++)
        cout << a[i] * tmp % mod << " \n"[i == n + m];

    return 0;
}