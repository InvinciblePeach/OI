#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 2e5 + 10, MAXK = 15, mod = 998244353;
int n, k, ans, C[MAXK][MAXK], s[MAXN];

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
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        (s[i] += s[i - 1]) %= mod;
    }
    C[0][0] = 1;
    for (int i = 1; i <= k; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    for (int i = 0; i <= k; i++) {
        int res = 0, sum = 0;
        for (int r = 0; r <= n; r++) {
            (res += qpow(s[r], i) * sum % mod) %= mod;
            (sum += qpow(mod - s[r], k - i)) %= mod;
        }
        (ans += C[k][i] * res % mod) %= mod;
    }
    cout << (ans + mod) % mod << '\n';

    return 0;
}