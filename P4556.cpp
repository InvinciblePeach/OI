#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int n, m, tot, mx, x[MAXN], y[MAXN], z[MAXN], fa[MAXN][18], dep[MAXN], rt[MAXN],
    ans[MAXN];
vector<int> g[MAXN];

struct Node {
    int l, r, lc, rc;
    int d, col;
} t[MAXN << 2];

void dfs(int u) {
    for (int i = 1; i < 18; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (auto v : g[u]) {
        if (v == fa[u][0]) continue;
        fa[v][0] = u, dep[v] = dep[u] + 1, dfs(v);
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int d = dep[u] - dep[v];
    for (int i = 0; d; d >>= 1, i++)
        if (d & 1) u = fa[u][i];
    if (u == v) return u;
    for (int i = 17; ~i; i--) {
        if (fa[u][i] == fa[v][i]) continue;
        u = fa[u][i], v = fa[v][i];
    }
    return fa[u][0];
}

void pushup(int p) {
    if (t[t[p].lc].d >= t[t[p].rc].d)
        t[p].d = t[t[p].lc].d, t[p].col = t[t[p].lc].col;
    else
        t[p].d = t[t[p].rc].d, t[p].col = t[t[p].rc].col;
}

int Modify(int p, const int &l, const int &r, const int &pos, const int &val) {
    if (!p) p = ++tot;
    t[p].l = l, t[p].r = r;
    if (t[p].l == t[p].r) return t[p].d += val, t[p].col = pos, p;

    int mid = (l + r) >> 1;
    if (pos <= mid) t[p].lc = Modify(t[p].lc, l, mid, pos, val);
    else t[p].rc = Modify(t[p].rc, mid + 1, r, pos, val);
    return pushup(p), p;
}

int Merge(const int &p, const int &q) {
    if (!p || !q) return p | q;
    if (t[p].l == t[p].r) return t[p].d += t[q].d, t[p].col = t[p].l, p;

    t[p].lc = Merge(t[p].lc, t[q].lc), t[p].rc = Merge(t[p].rc, t[q].rc);
    return pushup(p), p;
}

void solve(int u) {
    for (auto v : g[u]) {
        if (v == fa[u][0]) continue;
        solve(v);
        rt[u] = Merge(rt[u], rt[v]);
    }
    if (t[rt[u]].d) ans[u] = t[rt[u]].col;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].emplace_back(v), g[v].emplace_back(u);
    }
    dfs(1);
    for (int i = 1, x, y, z; i <= m; i++) {
        cin >> x >> y >> z;
        int t = lca(x, y);
        rt[x] = Modify(rt[x], 1, 1e5, z, 1);
        rt[y] = Modify(rt[y], 1, 1e5, z, 1);
        rt[t] = Modify(rt[t], 1, 1e5, z, -1);
        if (fa[t][0]) rt[fa[t][0]] = Modify(rt[fa[t][0]], 1, 1e5, z, -1);
    }
    solve(1);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << '\n';

    return 0;
}
