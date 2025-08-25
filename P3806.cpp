#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e4 + 10, MAXM = 110, MAXV = 1e7 + 10;
int n, m, rt, S, dis[MAXN], siz[MAXN], mx[MAXN], q[MAXM];
int st[MAXN], tot, del[MAXN], tp;
bitset<MAXN> vis;
bitset<MAXM> ans;
bitset<MAXV> bsk;

struct Edge {
    int v, w;

    Edge() {}
    Edge(int &V, int &W) : v(V), w(W) {}
};
vector<Edge> g[MAXN];

void find(int u, int fa) {
    siz[u] = 1, mx[u] = 0;
    for (auto e : g[u]) {
        auto [v, w] = e;
        if (vis[v] || v == fa) continue;
        find(v, u);
        siz[u] += siz[v], mx[u] = max(mx[u], siz[v]);
    }
    mx[u] = max(mx[u], S - siz[u]);
    if (mx[u] < mx[rt]) rt = u;
}

void dfs(int u, int fa) {
    st[++tot] = dis[u];
    for (auto e : g[u]) {
        auto [v, w] = e;
        if (vis[v] || v == fa) continue;
        dis[v] = dis[u] + w;
        dfs(v, u);
    }
}

void calc(int u) {
    bsk[0] = 1, tp = 0;
    for (auto e : g[u]) {
        auto [v, w] = e;
        if (vis[v]) continue;
        dis[v] = w, tot = 0;
        dfs(v, u);

        for (int i = 1; i <= tot; i++)
            for (int j = 1; j <= m; j++)
                if (q[j] >= st[i] && bsk[q[j] - st[i]]) ans[j] = 1;
        for (int i = 1; i <= tot; i++)
            if (st[i] <= 1e7) bsk[st[i]] = 1, del[++tp] = st[i];
    }
    while (tp)
        bsk[del[tp--]] = 0;
}

void solve(int u) {
    vis[u] = 1, calc(u);
    for (auto e : g[u]) {
        auto [v, w] = e;
        if (vis[v]) continue;
        find(v, u);
        S = siz[v], mx[rt = 0] = INT_MAX;
        find(v, u);
        solve(rt);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, u, v, w; i < n; i++) {
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    for (int i = 1; i <= m; i++) cin >> q[i];
    S = n;
    solve(1);
    for (int i = 1; i <= m; i++)
        cout << (ans[i] ? "AYE\n" : "NAY\n");

    return 0;
}