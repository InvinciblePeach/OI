#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

int n, k, m, mod, ans;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        b >>= 1, (a *= a) %= mod;
    }
    return res;
}

int gcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int res = gcd(b, a % b, y, x);
    y -= a / b * x;
    return res;
}

int inv(int p) {
    static int x, y;
    gcd(p, mod, x, y);
    return x;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> k >> m >> mod;
    n %= mod;
    int tmp = m * (m + 1) % mod * inv(2) % mod;
    ans = n * qpow(m, k - 1) % mod - qpow(m, k - 2) * (k - 1) % mod * tmp % mod;
    cout << (ans % mod + mod) % mod;

    return 0;
}