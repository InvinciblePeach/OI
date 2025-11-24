#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e6 + 10, mod = 1e9 + 7;
int T, n, m, frac[MAXN], ans, sum[MAXN];

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        (a *= a) %= mod, b >>= 1;
    }
    return res;
}

int inv(int x) { return qpow(x, mod - 2); }

int C(int x, int y) { return frac[x] * inv(frac[y]) % mod * inv(frac[x - y]) % mod; }

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    frac[0] = 1;
    for (int i = 1; i < MAXN; i++) frac[i] = frac[i - 1] * i % mod;
    for (int i = 0; i < MAXN; i++) {
        sum[i] = (i & 1 ? -1 : 1) * inv(frac[i]);
        if (i > 0) (sum[i] += sum[i - 1]) %= mod;
    }
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m;
        ans = frac[n] * inv(frac[m]) % mod * sum[n - m] % mod;
        cout << (ans + mod) % mod << '\n';
    }

    return 0;
}