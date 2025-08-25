#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 1e5 + 10, mod = 1e9 + 7;
int n, m;

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

int C(int a, int b) {
    int res = 1;
    for (int i = a; i > a - b; i--) (res *= i) %= mod;
    for (int i = 1; i <= b; i++) (res *= inv(i)) %= mod;
    return res;
}

int frac(int a) {
    int res = 1;
    for (int i = 2; i <= a; i++) (res *= i) %= mod;
    return res;
}

signed main() {
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;

    int tmp = ((n * n) % mod - C(n - 1, 2) + mod) % mod;
    cout << frac(n - 2) * C((tmp + m - n + mod) % mod, m - n + 1) % mod << '\n';

    return 0;
}