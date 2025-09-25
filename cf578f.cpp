#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 210;
int n, m, mod, fa[MAXN * MAXN], num[MAXN * MAXN];
string s[MAXN];

int id(int a, int b) { return (a - 1) * (m + 1) + b; }

int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }

void merge(int u, int v) {
    u = get(u), v = get(v);
    if (u == v) {
        cout << '0\n';
        exit(0);
    }
    fa[get(u)] = get(v);
}

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        if (b >>= 1) (a *= a) %= mod;
    }
    return res;
}

int inv(int x) { return qpow(x, mod - 2); }

struct Matrix {
    int mat[MAXN * 5][MAXN * 5];
    int N = 0;

    void add(int u, int v) {
        mat[u][u]++, mat[v][v]++;
        mat[u][v]--, mat[v][u]--;
    }

    int det() {
        int res = 1;
        for (int i = 1; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                while (mat[i][i]) {
                    int tmp = mat[j][i] / mat[i][i];
                    for (int k = i; k < N; k++) (mat[j][k] -= tmp * mat[i][k] % mod) %= mod;
                    swap(mat[i], mat[j]), res = -res;
                }
                swap(mat[i], mat[j]), res = -res;
            }
            (res *= mat[i][i]) %= mod;
        }
        return (res + mod) % mod;
    }
} g[2];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> mod;
    for (int i = 1; i <= n; i++) cin >> s[i], s[i] = ' ' + s[i];
    for (int i = 1; i <= (n + 1) * (m + 1); i++) fa[i] = i;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i][j] == '/')
                merge(id(i + 1, j), id(i, j + 1));
            else if (s[i][j] == '\\')
                merge(id(i, j), id(i + 1, j + 1));
        }
    }
    for (int i = 1; i <= n + 1; i++)
        for (int j = 1; j <= m + 1; j++)
            if (get(id(i, j)) == id(i, j)) g[(i + j) & 1].N++, num[id(i, j)] = g[(i + j) & 1].N;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i][j] == '*') {
                g[(i + j) & 1].add(num[get(id(i, j))], num[get(id(i + 1, j + 1))]);
                g[(i + j + 1) & 1].add(num[get(id(i + 1, j))], num[get(id(i, j + 1))]);
            }
        }
    }
    int ans = (g[0].det() + g[1].det());
    cout << (ans + mod) % mod << '\n';
    return 0;
}