#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int mod = 1e9 + 7;
int T, n, ans;

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

    cin >> T;
    while (T --> 0) {
        cin >> n;
        ans = 0;
        for (int i = 1; i <= sqrt(n); i++) {
            if (n % i) continue;
            (ans += qpow(n, n / i) * phi(i) % mod) %= mod;
            if ((i * i) ^ n) (ans += qpow(n, i) * phi(n / i) % mod) %= mod;
        }
        cout << ans * inv(n) % mod << '\n';
    }

    return 0;
}