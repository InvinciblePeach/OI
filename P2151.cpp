#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 140, mod = 45989;
int n, m, k, s, t, cnt, ans;

struct Edge {
    int u, v;
} e[MAXN];

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
        for (int i = 1; i <= cnt; i++)
            for (int k = 1; k <= cnt; k++)
                for (int j = 1; j <= cnt; j++)
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
    s++, t++;
    e[++cnt] = {0, s};
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v, u++, v++;
        e[++cnt] = {u, v};
        e[++cnt] = {v, u};
    }
    for (int i = 1; i <= cnt; i++)
        for (int j = 1; j <= cnt; j++)
            if (i != j && i != (j ^ 1))
                if (e[i].v == e[j].u) g[i][j] = 1;

    auto res = qpow(g, k);
    for (int i = 1; i <= cnt; i++)
        if (e[i].v == t)
            (ans += res[1][i]) %= mod;
    cout << ans << '\n';

    return 0;
}