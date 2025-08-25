#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 110, mod = 2009;
int n, t;

int pos(int i, int t) { return i + t * n; }

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
        for (int i = 1; i <= n * 9; i++)
            for (int k = 1; k <= n * 9; k++)
                for (int j = 1; j <= n * 9; j++)
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

    cin >> n >> t;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 8; j++) g[pos(i, j)][pos(i, j - 1)] = 1;
        for (int j = 1; j <= n; j++) {
            static char c;
            cin >> c, c -= '0';
            if (c) g[i][pos(j, int(c - 1))] = 1;
        }
    }
    cout << qpow(g, t)[1][n] << '\n';

    return 0;
}