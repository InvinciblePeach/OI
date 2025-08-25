#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 3e5 + 10, INF = 0x3f3f3f3f;
int n, T, tot, tmp[MAXN], key[MAXN], dp[MAXN], f[MAXN];
int id[MAXN], siz[MAXN], dep[MAXN], fa[MAXN][20];
int st[MAXN], top, ans[MAXN];
vector<int> g[MAXN], t[MAXN];
bitset<MAXN> vis;

void dfs(int u) {
    id[u] = ++tot, siz[u] = 1;
    for (int i = 1; i < 20; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    
    for (auto v : g[u]) {
        if (v == fa[u][0]) continue;
        fa[v][0] = u, dep[v] = dep[u] + 1;
        dfs(v);
        siz[u] += siz[v];
    }
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    int d = dep[a] - dep[b];
    for (int i = 0; d; i++, d >>= 1)
        if (d & 1) a = fa[a][i];
    if (a == b) return b;

    for (int i = 19; ~i; i--)
        if (fa[a][i] != fa[b][i]) a = fa[a][i], b = fa[b][i];
    return fa[a][0];
}

void insert(int u) {
    if (!top) return st[top = 1] = 1, void();

    int tmp = lca(st[top], u);
    while (top > 1 && dep[tmp] < dep[st[top - 1]]) {
        t[st[top - 1]].emplace_back(st[top]);
        top--;
    }
    if (dep[tmp] < dep[st[top]]) t[tmp].emplace_back(st[top--]);
    if (!top || st[top] != tmp) st[++top] = tmp;
    st[++top] = u;
}

void dfs2(int u) {
    dp[u] = INF;
    for (auto v : t[u]) {
        dfs2(v);
        int dis = dep[v] - dep[u];
        if (dp[v] + dis < dp[u]) dp[u] = dp[v] + dis, f[u] = f[v];
        else if (dp[v] + dis == dp[u]) f[u] = min(f[u], f[v]);
    }
    if (vis[u]) dp[u] = 0, f[u] = u;
}

void calc(int x, int y) {
    assert(dep[x] < dep[y]);
    int p = y, q = y;
    for (int i = 19; ~i; i--)
        if (dep[fa[p][i]] > dep[x]) p = fa[p][i];
    ans[f[x]] -= siz[p];
    for (int i = 19; ~i; i--) {
        int ydis = dep[y] - dep[fa[q][i]] + dp[y],
            xdis = dep[fa[q][i]] - dep[x] + dp[x];
        if (dep[fa[q][i]] > dep[x] && (ydis < xdis || (ydis == xdis && f[y] < f[x]))) q = fa[q][i];
    }
    ans[f[y]] += siz[q] - siz[y], ans[f[x]] += siz[p] - siz[q];
}

void dfs3(int u) {
    for (auto v : t[u]) {
        int dis = dep[v] - dep[u];
        if (dp[u] + dis < dp[v]) dp[v] = dp[u] + dis, f[v] = f[u];
        else if (dp[u] + dis == dp[v]) f[v] = min(f[v], f[u]);
        calc(u, v);
        dfs3(v);
    }
    ans[f[u]] += siz[u];
    vis[u] = 0;
    t[u].clear();
}

void solve() {
    static int m;
    cin >> m;
    for (int i = 1; i <= m; i++)
        cin >> key[i], vis[tmp[i] = key[i]] = 1, ans[key[i]] = 0;
    sort(key + 1, key + 1 + m,
         [](const int &a, const int &b) -> bool { return id[a] < id[b]; });
    if (key[1] != 1) st[top = 1] = 1;
    for (int i = 1; i <= m; i++)
        insert(key[i]);
    if (top)
        while (--top)
            t[st[top]].emplace_back(st[top + 1]);
    dfs2(1), dfs3(1);
    for (int i = 1; i <= m; i++) cout << ans[tmp[i]] << " \n"[i == m];
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs(1);
    cin >> T;
    while (T --> 0) solve();

    return 0;
}