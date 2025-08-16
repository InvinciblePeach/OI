#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 3e5 + 10;
int n, T, tot, key[MAXN], dp[MAXN], id[MAXN], dep[MAXN], fa[MAXN][20], mn[MAXN][20];
int st[MAXN], top;

struct Edge {
    int v, w;
    Edge(int V, int W) : v(V), w(W) {}
};
vector<Edge> g[MAXN], t[MAXN];
bitset<MAXN> vis;

void dfs(int u) {
    id[u] = ++tot;
    for (int i = 1; i < 20; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1], mn[u][i] = min(mn[u][i - 1], mn[fa[u][i - 1]][i - 1]);

    for (auto e : g[u]) {
        int v = e.v, w = e.w;
        if (v == fa[u][0]) continue;
        fa[v][0] = u, dep[v] = dep[u] + 1, mn[v][0] = w;
        dfs(v);
    }
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = 19; ~i; i--)
        if (dep[fa[a][i]] >= dep[b]) a = fa[a][i];
    assert(dep[a] == dep[b]);
    if (a == b) return a;
    for (int i = 19; ~i; i--)
        if (fa[a][i] ^ fa[b][i]) a = fa[a][i], b = fa[b][i];
    return fa[a][0];
}

int calc(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int res = LLONG_MAX;
    for (int i = 19; ~i; i--)
        if (dep[fa[u][i]] >= dep[v]) res = min(res, mn[u][i]), u = fa[u][i];
    return res;
}

void addvt(int u, int v) { t[u].emplace_back(v, calc(u, v)); }

void insert(int u) {
    if (!top) return st[top = 1] = 1, void();

    int tmp = lca(st[top], u);
    while (top > 1 && dep[tmp] < dep[st[top - 1]]) {
        addvt(st[top - 1], st[top]);
        top--;
    }
    if (dep[tmp] < dep[st[top]]) addvt(tmp, st[top--]);
    if (!top || st[top] != tmp) st[++top] = tmp;
    st[++top] = u;
}

void dfs2(int u) {
    dp[u] = 0;
    for (auto e : t[u]) {
        int v = e.v, w = e.w;
        dfs2(v);
        if (vis[v])
            dp[u] += w;
        else
            dp[u] += min(dp[v], w);
    }
    t[u].clear();
}

void solve() {
    static int m;
    cin >> m;
    for (int i = 1; i <= m; i++) cin >> key[i], vis[key[i]] = 1;
    sort(key + 1, key + 1 + m, [](const int &a, const int &b) -> bool { return id[a] < id[b]; });
    if (key[1] != 1) st[top = 1] = 1;
    for (int i = 1; i <= m; i++) insert(key[i]);
    if (top)
        while (--top) addvt(st[top], st[top + 1]);
    dfs2(1);
    cout << dp[1] << '\n';
    for (int i = 1; i <= m; i++) vis[key[i]] = 0;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1, u, v, w; i < n; i++) {
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    dep[1] = 1;
    dfs(1);
    cin >> T;
    while (T-- > 0) solve();

    return 0;
}