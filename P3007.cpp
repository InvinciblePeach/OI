#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 4010;
int n, m, tot, cnt, top, st[MAXN], dfn[MAXN], low[MAXN], scc[MAXN];
bitset<MAXN> vis;
vector<int> g[MAXN], t[MAXN];

void tarjan(int u) {
    vis[u] = 1;
    dfn[u] = low[u] = ++tot;
    st[++top] = u;
    for (auto v : g[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        vis[u] = 0, scc[u] = ++cnt;
        while (st[top] != u)
            vis[st[top]] = 0, scc[st[top]] = cnt, top--;
        top--;
    }
}

void dfs(int u) {
    vis[u] = 1;
    for (auto v : t[u]) {
        if (vis[v]) continue;
        dfs(v);
    }
}

bool check(int u) {
    vis.reset();
    dfs(u);
    for (int i = 1; i <= n; ++i)
        if (vis[scc[i]] && vis[scc[i + n]]) return false;
    return true;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        static int u, v;
        static char x, y;
        cin >> u >> x >> v >> y;
        if (x == 'Y' && y == 'Y') {
            g[u + n].emplace_back(v);
            g[v + n].emplace_back(u);
        } else if (x == 'N' && y == 'Y') {
            g[u].emplace_back(v);
            g[v + n].emplace_back(u + n);
        } else if (x == 'Y' && y == 'N') {
            g[v].emplace_back(u);
            g[u + n].emplace_back(v + n);
        } else if (x == 'N' && y == 'N') {
            g[u].emplace_back(v + n);
            g[v].emplace_back(u + n);
        }
    }
    for (int i = 1; i <= (n << 1); i++)
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n; i++)
        if (scc[i] == scc[i + n]) return cout << "IMPOSSIBLE\n", 0;

    for (int u = 1; u <= (n << 1); u++)
        for (auto v : g[u])
            if (scc[u] != scc[v]) t[scc[u]].emplace_back(scc[v]);
    for (int i = 1; i <= n; i++) {
        bool x = check(scc[i]), y = check(scc[i + n]);
        if (x && y) cout << "?";
        if (x && !y) cout << "Y";
        if (!x && y) cout << "N";
    }
    cout << '\n';
    return 0;
}