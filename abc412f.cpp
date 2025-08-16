#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 3e5 + 10, mod = 998244353;
int n, c, sum = 1, a[MAXN], dp[MAXN], x, y;

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

    cin >> n >> c;
    for (int i = 1; i <= n; i++) cin >> a[i], sum += a[i];
    a[c]++;
    int tmp = a[c];
    sort(a + 1, a + 1 + n);
    c = lower_bound(a + 1, a + 1 + n, tmp) - a;
    assert(tmp == a[c]);

    for (int i = 1; i <= n; i++) (x += a[i] * inv(sum) % mod) %= mod;
    for (int i = n; i; i--) {
        x = ((x - a[i]) % mod + mod) % mod;
        dp[i] = (1 + y) * inv((1 - x + mod) % mod) % mod;
        (y += a[i] * dp[i] % mod * inv(sum) % mod) %= mod;
    }
    cout << dp[c] << '\n';

    return 0;
}