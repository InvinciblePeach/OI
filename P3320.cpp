#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;
int n, m, ans, dfn[MAXN], id[MAXN], tot, dis[MAXN], dep[MAXN], fa[MAXN][21];
set<int> s;
bitset<MAXN> vis;
struct Edge {
    int v, w;

    Edge() {}
    Edge(int V, int W) : v(V), w(W) {}
};
vector<Edge> g[MAXN];

void dfs(int u) {
    dfn[id[u] = ++tot] = u;
    for (int j = 1; j <= 20; j++) fa[u][j] = fa[fa[u][j - 1]][j - 1];
    for (auto [v, w] : g[u]) {
        if (v == fa[u][0]) continue;
        fa[v][0] = u, dep[v] = dep[u] + 1, dis[v] = dis[u] + w, dfs(v);
    }
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = 20; ~i; i--)
        if (dep[fa[a][i]] >= dep[b]) a = fa[a][i];
    if (a == b) return a;
    for (int i = 20; ~i; i--)
        if (fa[a][i] ^ fa[b][i]) a = fa[a][i], b = fa[b][i];
    return fa[a][0];
}

int calc(int x, int y) { return dis[x] + dis[y] - (dis[lca(x, y)] << 1); }

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, u, v, w; i < n; i++) {
        cin >> u >> v >> w;
        g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    }
    dfs(1);
    while (m --> 0) {
        static int x, y, z;
        static set<int>::iterator it;
        cin >> x;
        x = id[x];
        if (!vis[dfn[x]]) s.insert(x);
        y = dfn[(it = s.lower_bound(x)) == s.begin() ? *s.rbegin() : *--it];
        z = dfn[(it = s.upper_bound(x)) == s.end() ? *s.begin() : *it];
        if (vis[dfn[x]]) s.erase(x);
        x = dfn[x];
        auto d = calc(x, y) + calc(x, z) - calc(y, z);
        if (!vis[x]) vis[x] = 1, ans += d;
        else vis[x] = 0, ans -= d;
        cout << ans << '\n';
    }

    return 0;
}