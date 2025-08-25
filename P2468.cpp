#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 4e4, mod = 999911658;
int n, g, ans, frac[MAXN], a[5], b[5] = {0, 2, 3, 4679, 35617};

void init(int p) {
    frac[0] = 1;
    for (int i = 1; i <= p; i++) frac[i] = frac[i - 1] * i % p;
}

int qpow(int a, int b, int p) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= p;
        (a *= a) %= p;
        b >>= 1;
    }
    return res;
}

int inv(int x, int p) { return qpow(x, p - 2, p); }

int C(int n, int m, int p) { return n < m ? 0 : frac[n] * inv(frac[m], p) % p * inv(frac[n - m], p) % p; }

int lucas(int n, int m, int p) {
    if (n < m) return 0;
    if (!n) return 1;
    return lucas(n / p, m / p, p) * C(n % p, m % p, p) % p;
}

void crt() {
    for (int i = 1; i <= 4; i++)
        (ans += a[i] * (mod / b[i]) % mod * inv(mod / b[i], b[i]) % mod) %= mod;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> g;
    if (!(g % (mod + 1))) return cout << "0\n", 0;

    for (int k = 1; k <= 4; k++) {
        init(b[k]);
        for (int i = 1; i * i <= n; i++) {
            if (n % i) continue;
            (a[k] += lucas(n, i, b[k])) %= b[k];
            if ((i * i) ^ n) (a[k] += lucas(n, n / i, b[k])) %= b[k];
        }
    }
    crt();
    cout << qpow(g, ans, mod + 1) << '\n';

    return 0;
}