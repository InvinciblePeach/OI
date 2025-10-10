#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e5 + 10;
int T, n, m, res, s[MAXN][2], d[MAXN], dep[MAXN], fa[MAXN], siz[MAXN], top[MAXN], son[MAXN], ans[MAXN];
vector<pii> g[MAXN];

struct Edge {
    int u, v;
} e[MAXN];

void dfs1(int u) {
    siz[u] = 1;
    for (auto [v, w] : g[u]) {
        if (v == fa[u]) continue;
        fa[v] = u, dep[v] = dep[u] + 1, d[v] = d[u] + w;
        dfs1(v);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int top) {
    ::top[u] = top;
    if (son[u]) dfs2(son[u], top);
    for (auto [v, w] : g[u]) {
        if (v == son[u] || v == fa[u]) continue;
        dfs2(v, v);
    }
}

int lca(int x, int y) {
    while (top[x] ^ top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}

int dis(int x, int y) { return d[x] + d[y] - (d[lca(x, y)] << 1); }

namespace dsu {
    int fa[MAXN];
    void init() {
        for (int i = 1; i <= n; i++) fa[i] = i;
    }

    int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }

    void merge(int x, int y) {
        x = get(x), y = get(y);
        fa[y] = x;
        int mx = 0;
        int now[] = {s[x][0], s[x][1], s[y][0], s[y][1]};
        for (int i = 0; i < 4; i++) {
            for (int j = i + 1; j < 4; j++) {
                int nowx = now[i], nowy = now[j];
                int d = dis(nowx, nowy);
                if (d > mx) mx = d, s[x][0] = nowx, s[x][1] = nowy;
            }
        }
        res = max(res, mx);
    }
} // namespace dsu

int qry[MAXN];
bitset<MAXN> vis;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T-- > 0) {
        cin >> n >> m;
        res = 0;
        for (int i = 1; i <= n; i++) g[i].clear(), son[i] = vis[i] = 0;
        for (int i = 1, u, v, w; i < n; i++) {
            cin >> u >> v >> w;
            e[i] = {u, v};
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }
        dsu::init();
        dfs1(1), dfs2(1, 1);
        for (int i = 1; i <= n; i++) s[i][0] = s[i][1] = i;
        for (int i = 1; i <= m; i++) vis[cin >> qry[i], qry[i]] = 1;
        for (int i = 1; i < n; i++)
            if (!vis[i]) dsu::merge(e[i].u, e[i].v);
        for (int i = m; i; i--) {
            ans[i] = res;
            auto id = qry[i];
            dsu::merge(e[id].u, e[id].v);
        }
        for (int i = 1; i <= m; i++) cout << ans[i] << '\n';
    }

    return 0;
}