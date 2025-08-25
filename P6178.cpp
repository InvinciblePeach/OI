#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 310, mod = 1e9 + 7;
int n, m, t, L[MAXN][MAXN];

int det(int mat[][MAXN]) {
    int res = 1;
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            while (mat[i][i]) {
                int tmp = mat[j][i] / mat[i][i];
                for (int k = i; k < n; k++)
                    (mat[j][k] -= tmp * mat[i][k] % mod) %= mod;
                swap(mat[i], mat[j]), res = -res;
            }
            swap(mat[i], mat[j]), res = -res;
        }
        (res *= mat[i][i]) %= mod;
    }
    return (res + mod) % mod;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> t;
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        u--, v--;
        if (t) {
            (L[v][u] -= w) %= mod;
            (L[v][v] += w) %= mod;
        } else {
            (L[u][v] -= w) %= mod;
            (L[u][u] += w) %= mod;
            (L[v][u] -= w) %= mod;
            (L[v][v] += w) %= mod;
        }
    }
    cout << det(L) << '\n';

    return 0;
}