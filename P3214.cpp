#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e6 + 10, mod = 1e8 + 7;
int n, m, tot = 1, tmp = 1, A[MAXN], dp[MAXN];

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        b >>= 1, (a *= a) %= mod;
    }
    return res;
}

int inv(int x) { return qpow(x, mod - 2); }

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) (tot <<= 1) %= mod;
    A[0] = 1, dp[0] = 1;
    for (int i = 1; i <= m; i++) A[i] = A[i - 1] * (tot - i) % mod, (tmp *= i) %= mod;
    for (int i = 2; i <= m; i++) dp[i] = (A[i - 1] - dp[i - 1] - dp[i - 2] * (i - 1) % mod * (tot - i + 1) % mod) % mod;
    cout << (dp[m] * inv(tmp) % mod + mod) % mod << '\n';

    return 0;
}