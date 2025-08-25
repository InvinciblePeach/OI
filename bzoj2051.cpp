#include <bits/stdc++.h>
#define int long long

using namespace std;

const int mod = 1e4;
int n, ans, cnt;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}

signed main() {
    freopen("mult.in", "r", stdin);
    freopen("mult.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;

    int d = 1, x = 1;
    for (; x * 10 - 1 <= n; x *= 10, d++) (cnt += 9 * x * d % mod) %= mod;
    (cnt += d * (n - x + 1) % mod) %= mod;

    if (n == 1) return cout << 4 << '\n', 0;

    ans = n % mod;
    (ans += n * qpow(2, n - 1)) %= mod;
    (ans += cnt - 1) %= mod;
    (ans += cnt * qpow(2, n - 1)) %= mod;
    (ans += qpow(2, n) - 1) %= mod;
    (ans += ((n - 1) << 1) % mod) %= mod;
    cout << ans << '\n';

    return 0;
}