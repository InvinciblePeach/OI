#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int mod = 3214567;
int n, m, r, k, ans;

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

int phi(int x) {
    int res = x;
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i) continue;
        res -= res / i;
        while (!(x % i)) x /= i;
    }
    if (x ^ 1) res -= res / x;
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> r;
    for (int i = 1; i * i <= m; i++) {
        if (m % i) continue;
        (k += qpow(r, m / i) * phi(i) % mod) %= mod;
        if ((i * i) ^ m) (k += qpow(r, i) * phi(m / i) % mod) %= mod;
    }
    (k *= inv(m)) %= mod;
    ans = (qpow(k - 1, n) + ((n & 1) ? -1 : 1) * (k - 1)) % mod;
    cout << (ans + mod) % mod << '\n';

    return 0;
}