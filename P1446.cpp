#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 70;
bool flag;
int r, g, b, n, m, mod, ans;
int to[MAXN], siz[MAXN], f[MAXN][MAXN][MAXN];
bitset<MAXN> vis;

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

int calc() {
    int tot = 0;
    memset(f, 0, sizeof(f));
    vis.reset();
    for (int i = 1, p, len; i <= n; i++) {
        if (vis[i]) continue;
        p = i, len = 0;
        while (!vis[p]) len++, vis[p] = 1, p = to[p];
        siz[++tot] = len;
    }
    f[0][0][0] = 1;
    for (int w = 1; w <= tot; w++)
        for (int i = r; ~i; i--)
            for (int j = g; ~j; j--)
                for (int k = b; ~k; k--) {
                    if (i >= siz[w]) (f[i][j][k] += f[i - siz[w]][j][k]) %= mod;
                    if (j >= siz[w]) (f[i][j][k] += f[i][j - siz[w]][k]) %= mod;
                    if (k >= siz[w]) (f[i][j][k] += f[i][j][k - siz[w]]) %= mod;
                }
    return f[r][g][b];
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> r >> g >> b >> m >> mod;
    n = r + g + b;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) cin >> to[j];
        bool flag = 1;
        for (int j = 1; j <= n; j++) if (to[j] ^ j) flag = 0;
        if (flag) ::flag = 1;
        (ans += calc()) %= mod;
    }
    if (!flag) {
        m++;
        for (int j = 1; j <= n; j++) to[j] = j;
        (ans += calc()) %= mod;
    }
    cout << ans * inv(m) % mod << '\n';

    return 0;
}