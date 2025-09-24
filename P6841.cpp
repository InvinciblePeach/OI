#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 131, mod = 1e9 + 7;
int n, m;

struct Matrix {
    int g[MAXN][MAXN];

    constexpr auto operator[](const int &x) { return g[x]; }

    Matrix(bool x) {
        for (int i = 0; i < MAXN; i++)
            for (int j = 0; j < MAXN; j++) g[i][j] = x * (i == j);
    }

    Matrix operator*(const Matrix &o) {
        Matrix res(0);
        for (int i = 0; i < MAXN; i++)
            for (int k = 0; k < MAXN; k++)
                for (int j = 0; j < MAXN; j++) (res[i][j] += g[i][k] * o.g[k][j] % mod) %= mod;
        return res;
    }
} g(0);

Matrix qpow(Matrix a, int b) {
    Matrix res(1);
    while (b) {
        if (b & 1) res = res * a;
        if (b >>= 1) a = a * a;
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 0; i < 26; i++) g[i][i + 26] = g[i + 26][i + 52] = g[i + 52][i + 78] = g[i + 78][i + 104] = 1;
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++) g[i][j] = g[j][i] = 1;
    for (int i = 1; i <= m; i++) {
        static char a, b;
        static int x;
        cin >> a >> b >> x;
        g[a - 'a'][b - 'a'] = g[b - 'a'][a - 'a'] = 0;
        g[a - 'a' + 26 * (x - 1)][b - 'a'] = g[b - 'a' + 26 * (x - 1)][a - 'a'] = 1;
    }
    for (int i = 0; i < 26; i++) g[130][i] = 1;
    g[130][130] = 1;
    g = qpow(g, n + 1);
    int ans = 0;
    for (int i = 0; i < 26; i++) (ans += g[130][i]) %= mod;
    cout << ans << '\n';
    return 0;
}