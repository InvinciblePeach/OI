#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 110, mod = 1e9 + 7;
int n, m, k, ans, U[MAXN], R[MAXN], C[MAXN][MAXN], h[MAXN];
int y[MAXN], pre[MAXN], suf[MAXN], frac[MAXN], invf[MAXN];

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

int calc(int x, int k) {
    pre[0] = x, suf[k + 2] = 1;
    for (int i = 1; i <= k + 1; i++) y[i] = (y[i - 1] + qpow(i, k)) % mod;
    for (int i = 1; i <= k + 1; i++) pre[i] = pre[i - 1] * (x - i) % mod;
    for (int i = k + 1; ~i; i--) suf[i] = suf[i + 1] * (x - i) % mod;
    
    int res = 0;
    for (int i = 1; i <= k + 1; i++)
        (res += y[i] * pre[i - 1] % mod * suf[i + 1] % mod * invf[i] % mod * invf[k + 1 - i] % mod * ((k + 1 - i) & 1 ? -1 : 1)) %= mod;
    return (res + mod) % mod;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) cin >> U[i];
    for (int i = 1; i <= m; i++) cin >> R[i];

    frac[0] = 1;
    for (int i = 1; i <= n + 5; i++) frac[i] = frac[i - 1] * i % mod;
    invf[n + 5] = inv(frac[n + 5]);
    for (int i = n + 4; ~i; i--) invf[i] = invf[i + 1] * (i + 1) % mod;
    C[0][0] = 1;
    for (int i = 1; i <= n; i++) { 
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }
    
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < R[i]; j++)
            (h[i] += C[R[i] - 1][j] * qpow(U[i], j) % mod * calc(U[i], n - j - 1) % mod * ((R[i] - 1 - j) & 1 ? -1 : 1)) %= mod;
        (h[i] += mod) %= mod;
    }
    for (int i = 1; i <= n; i++) cerr << (h[i] + mod) % mod << " \n"[i == n];

    for (int i = k; i <= n; i++) {
        int tmp = C[i][k] * C[n - 1][i] % mod;
        for (int j = 1; j <= m; j++) (tmp *= C[n - i - 1][R[j] - 1] * h[j] % mod) %= mod;
        (ans += tmp * ((i - k) & 1 ? -1 : 1)) %= mod;
    }
    cout << (ans + mod) % mod << '\n';

    return 0;
}