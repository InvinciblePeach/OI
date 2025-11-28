#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e4 + 10;
int n, m, tot, cnt, ans, a[MAXN], dfn[MAXN], low[MAXN], scc[MAXN], sum[MAXN], deg[MAXN], dis[MAXN];
int st[MAXN], top;
bitset<MAXN> vis;
vector<int> g[MAXN], h[MAXN];

void tarjan(int u) {
    dfn[u] = low[u] = ++tot;
    vis[u] = 1;
    st[++top] = u;
    for (auto v : g[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (low[u] >= dfn[u]) {
        scc[u] = ++cnt;
        do {
            scc[st[top]] = cnt;
            sum[cnt] += a[st[top]];
            vis[st[top]] = 0;
        } while (st[top--] ^ u);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        g[u].emplace_back(v);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }
    for (int u = 1; u <= n; u++)
        for (auto v : g[u])
            if (scc[v] ^ scc[u]) h[scc[u]].emplace_back(scc[v]), deg[scc[v]]++;
    queue<int> q;
    for (int i = 1; i <= cnt; i++)
        if (!deg[i]) q.emplace(i), dis[i] = sum[i];
    while (!q.empty()) {
        int u = q.front();
        ans = max(ans, dis[u]);
        q.pop();
        for (auto v : h[u]) {
            dis[v] = max(dis[v], dis[u] + sum[v]);
            if (!--deg[v]) q.emplace(v);
        }
    }
    cout << ans << '\n';

    return 0;
}