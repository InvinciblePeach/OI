#include <bits/stdc++.h>
#define int long long

using namespace std;

const int mod = 998244353;
int n;

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

    cin >> n;
    int ans = n % mod * ((n + 1) % mod) % mod * inv(2) % mod, sum = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        (sum += (r - l + 1) * (n / l) % mod) %= mod;
    }

    cout << (ans + mod - sum) % mod << "\n";
    return 0;
}
