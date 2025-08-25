#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 2010, mod = 998244353;
int n, k, ans, x[MAXN], y[MAXN];

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

    cin >> n >> k;
    n--;
    for (int i = 0; i <= n; i++) cin >> x[i] >> y[i];
    for (int i = 0; i <= n; i++) {
        int tmp = 1;
        for (int j = 0; j <= n; j++) {
            if (i == j) continue;
            (tmp *= (k - x[j])) %= mod;
            (tmp *= inv(x[i] - x[j])) %= mod;
        }
        (ans += tmp * y[i] % mod) %= mod;
    }
    cout << (ans + mod) % mod << '\n';

    return 0;
}