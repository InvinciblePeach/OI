#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 5e5 + 10, MAXM = 5e6;
int n, siz[MAXN], son[MAXN], dep[MAXN], dis[MAXN], ans[MAXN];
int q[MAXN], top, vis[MAXM];

struct Edge {
    int v, w;

    Edge() {}
    Edge(int V, int W) : v(V), w(W) {}
};
vector<Edge> g[MAXN];

void dfs(int u) {
    siz[u] = 1;
    for (auto [v, w] : g[u]) {
        dis[v] = dis[u] ^ w, dep[v] = dep[u] + 1;
        dfs(v), siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}

void insert(int u) { 
    q[++top] = u;
    vis[dis[u]] = max(vis[dis[u]], dep[u]);
}

void clean() {
    while (top) vis[dis[q[top--]]] = 0;
}

void calc(int u, int x) {
    if (vis[dis[u]]) ans[x] = max(ans[x], vis[dis[u]] + dep[u] - (dep[x] << 1));
    for (int i = 0; i < 22; i++)
        if (vis[dis[u] ^ (1 << i)]) ans[x] = max(ans[x], vis[dis[u] ^ (1 << i)] + dep[u] - (dep[x] << 1));
    for (auto [v, w] : g[u]) calc(v, x);
}

void add(int u) {
    insert(u);
    for (auto [v, w] : g[u]) add(v);
}

void solve(int u) {
    for (auto [v, w] : g[u]) {
        if (v == son[u]) continue;
        solve(v), clean(), ans[u] = max(ans[u], ans[v]);
    }
    if (son[u]) solve(son[u]), ans[u] = max(ans[u], ans[son[u]]);
    if (vis[dis[u]]) ans[u] = max(ans[u], vis[dis[u]] - dep[u]);
    for (int i = 0; i < 22; i++)
        if (vis[dis[u] ^ (1 << i)]) ans[u] = max(ans[u], vis[dis[u] ^ (1 << i)] - dep[u]);
    insert(u);
    for (auto [v, w] : g[u]) {
        if (v == son[u]) continue;
        calc(v, u);
        add(v);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cerr << (1 << 22) << '\n';
    cin >> n;
    for (int i = 2, fa; i <= n; i++) {
        static char w;
        cin >> fa >> w;
        g[fa].emplace_back(i, (1 << int(w - 'a')));
    }
    dfs(1), solve(1);
    for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];

    return 0;
}