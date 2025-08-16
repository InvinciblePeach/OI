#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 110, MAXV = 2e6 + 10, mod = 998244353;
int T, n, m, a[MAXN], b[MAXN], mat[MAXN][MAXN], frac[MAXV];

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        (a *= a) %= mod, b >>= 1;
    }
    return res;
}

int inv(int x) { return qpow(x, mod - 2); }

int C(int a, int b) { return frac[a] * inv(frac[b]) % mod * inv(frac[a - b]) % mod; }

int det(int mat[][MAXN]) {
    int res = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = i + 1; j <= m; j++) {
            while (mat[i][i]) {
                int t = mat[j][i] / mat[i][i];
                for (int k = i; k <= m; k++) (mat[j][k] -= t * mat[i][k] % mod) %= mod;
                swap(mat[i], mat[j]), res = -res;
            }
            swap(mat[i], mat[j]), res = -res;
        }
        (res *= mat[i][i]) %= mod;
    }
    return (res + mod) % mod;
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> a[i] >> b[i];

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++) mat[i][j] = (a[i] <= b[j] ? C(b[j] - a[i] + n - 1, n - 1) : 0);

    cout << det(mat) << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    frac[0] = 1;
    for (int i = 1; i < MAXV; i++) frac[i] = frac[i - 1] * i % mod;
    while (T-- > 0) solve();

    return 0;
}