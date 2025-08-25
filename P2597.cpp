#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 7e4 + 10;
int n, fa[MAXN][20], f[MAXN], dep[MAXN], deg[MAXN], siz[MAXN];
vector<int> g[MAXN], t[MAXN];
queue<int> q;

int lca(int x, int y) {
    if (dep[x] > dep[y]) swap(x, y);
    for (int i = 19; ~i; i--)
        if (dep[fa[y][i]] >= dep[x]) y = fa[y][i];
    if (x == y) return x;
    for (int i = 19; ~i; i--) {
        if (fa[x][i] ^ fa[y][i]) x = fa[x][i], y = fa[y][i];
    }
    return fa[x][0];
}

void dfs(int u) {
    siz[u] = 1;
    for (auto v : t[u]) {
        dfs(v);
        siz[u] += siz[v];
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    memset(f, -1, sizeof(f));
    for (int i = 1, u; i <= n; i++)
        while (cin >> u && u)
            g[u].emplace_back(i), deg[i]++;
    for (int i = 1; i <= n; i++)
        if (!deg[i]) q.emplace(i), f[i] = 0;
    while (q.size()) {
        int u = q.front();
        cerr << u << ' ' << f[u] << '\n';
        q.pop();
        t[f[u]].emplace_back(u);
        dep[u] = dep[fa[u][0] = f[u]] + 1;
        for (int i = 1; i < 20; i++)
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        for (auto v : g[u]) {
            if (~f[v])
                f[v] = lca(f[v], u);
            else
                f[v] = u;
            if (!--deg[v]) q.emplace(v);
        }
    }

    dfs(0);
    for (int i = 1; i <= n; i++)
        cout << siz[i] - 1 << '\n';

    return 0;
}