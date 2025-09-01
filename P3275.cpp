#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 1e5 + 10;
int n, m, dis[MAXN];
ll ans;
struct Edge {
    int v, w;
    Edge(int V, int W) : v(V), w(W) {}
};
vector<Edge> g[MAXN], t[MAXN];

namespace tarjan {
    int st[MAXN], top, cnt, dfn[MAXN], low[MAXN], tot, scc[MAXN], siz[MAXN];
    bitset<MAXN> vis;

    void tarjan(int u) {
        vis[st[++top] = u] = 1;
        dfn[u] = low[u] = ++tot;
        for (auto [v, w] : g[u]) {
            if (!dfn[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (vis[v])
                low[u] = min(low[u], dfn[v]);
        }
        if (dfn[u] == low[u]) {
            ++cnt;
            // siz[scc[u] = ++cnt]++, vis[u] = 0;
            do {
                siz[scc[st[top]] = cnt]++, vis[st[top]] = 0;
            } while (st[top--] ^ u);
        }
    }
} // namespace tarjan

int deg[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, op, u, v; i <= m; i++) {
        cin >> op >> u >> v;
        if (op == 1) g[u].emplace_back(v, 0), g[v].emplace_back(u, 0);
        if (op == 2) {
            if (u == v) {
                cout << "-1\n";
                return 0;
            }
            g[u].emplace_back(v, 1);
        }
        if (op == 3) g[v].emplace_back(u, 0);
        if (op == 4) {
            if (u == v) {
                cout << "-1\n";
                return 0;
            }
            g[v].emplace_back(u, 1);
        }
        if (op == 5) g[u].emplace_back(v, 0);
    }

    queue<int> q;
    for (int i = n; i; i--)
        g[0].emplace_back(i, 1);
    for (int i = 0; i <= n; i++) if (!tarjan::dfn[i]) tarjan::tarjan(i);
    using tarjan::scc, tarjan::siz, tarjan::cnt;
    for (int u = 0; u <= n; u++) {
        for (auto [v, w] : g[u]) {
            if (scc[u] == scc[v] && w) {
                cout << "-1\n";
                return 0;
            }
            if (scc[u] ^ scc[v]) t[scc[u]].emplace_back(scc[v], w), deg[scc[v]]++;
        }
    }
    for (int i = 1; i <= cnt; i++) if (!deg[i]) q.emplace(i);
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        for (auto [v, w] : t[u]) {
            dis[v] = max(dis[v], dis[u] + w);
            if (!--deg[v]) q.emplace(v);
        }
    }
    // for (int i = 0; i <= n; i++) cerr << scc[i] << " \n"[i == n];
    // for (int i = 1; i <= cnt; i++) cerr << dis[i] << ' ' << siz[i] << "\n";
    for (int i = 1; i <= tarjan::cnt; i++)
        ans += (ll)dis[i] * siz[i];
    cout << ans << '\n';

    return 0;
}