#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 130, mod = 45989;
int n, m, ans, k, s, t, u[MAXN], v[MAXN], cnt;

struct Matrix {
    int a[MAXN][MAXN];

    constexpr auto operator[](const int &x) { return a[x]; }

    Matrix(bool x) {
        for (int i = 0; i < MAXN; i++)
            for (int j = 0; j < MAXN; j++)
                a[i][j] = x * (i == j);
    }

    Matrix operator*(const Matrix &o) {
        Matrix res(0);
        for (int i = 1; i < cnt; i++)
            for (int k = 1; k < cnt; k++)
                for (int j = 1; j < cnt; j++)
                    (res[i][j] += a[i][k] * o.a[k][j] % mod) %= mod;
        return res;
    }
} g(0);

Matrix qpow(Matrix a, int b) {
    Matrix res(1);
    while (b) {
        if (b & 1) res = res * a;
        a = a * a, b >>= 1;
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> k >> s >> t;
    s++, t++, u[++cnt] = 0, v[cnt] = s;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v, u++, v++;    
        ::u[++cnt] = u, ::v[cnt] = v;
        ::u[++cnt] = v, ::v[cnt] = u;
    }
    for (int i = 1; i <= cnt; i++) {
        for (int j = 1; j <= cnt; j++) {
            if ((i ^ j) && (i ^ j ^ 1) && v[i] == u[j]) g[i][j] = 1;
        }
    }
    auto res = qpow(g, k);
    for (int i = 1; i <= cnt; i++) if (v[i] == t) (ans += res[1][i]) %= mod;
    cout << ans << '\n';

    return 0;
}