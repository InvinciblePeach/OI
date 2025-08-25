#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 5e5 + 10, mod = 1e9 + 7;
int n, m, p, tot, cnt, dfn[MAXN], low[MAXN], d[MAXN], scc[MAXN], w[MAXN], e[MAXN];
int st[MAXN], top, f[MAXN][2], siz[MAXN], ans;
vector<int> g[MAXN], t[MAXN];
bitset<MAXN> vis;

void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++tot;
    vis[st[++top] = u] = 1;
    for (auto v : g[u]) {
        if (v == fa) continue;
        if (!dfn[v]) tarjan(v, u), low[u] = min(low[u], low[v]);
        else if (vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        cnt++;
        do vis[st[top]] = 0, w[scc[st[top]] = cnt]++;
        while (st[top--] ^ u);
    }
}

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}

void dfs(int u, int fa) {
    siz[u] = e[u];
    for (auto v : t[u]) {
        if (v == fa) continue;
        dfs(v, u), siz[u] += siz[v] + 1;
    }
}

void dp(int u, int fa) {

    for (auto v : t[u]) {
        if (v == fa) continue;
        dp(v, u);
        f[u][1] = (f[u][1] * (((f[v][0] << 1) + f[v][1]) % mod) % mod + f[u][0] * f[v][1] % mod) % mod;
        f[u][0] = f[u][0] * ((f[v][0] << 1) % mod) % mod;
    }
    if (u == 1) ans = (ans + f[u][1]) % mod; // 特判 1 号结点的特殊情况
    else ans = (ans + f[u][1] * qpow(2, siz[1] - siz[u] - 1)) % mod;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        g[u].emplace_back(v), g[v].emplace_back(u);
    }
    tarjan(1, 0);
    for (int u = 1; u <= n; u++) {
        for (auto v : g[u]) {
            if (scc[u] ^ scc[v]) t[scc[u]].emplace_back(scc[v]);
            else e[scc[u]]++;
        }
    }
    for (int i = 1; i <= n; i++) {
        e[i] >>= 1;
        f[i][0] = qpow(2, e[i]);
        f[i][1] = qpow(2, w[i] + e[i]) - f[i][0];
    }
    dfs(1, 0), dp(1, 0);
    cout << ans << '\n';

    return 0;
}