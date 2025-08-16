#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;
int T, n, m, pos[MAXN];
int tot, cnt, top, st[MAXN], dfn[MAXN], low[MAXN], scc[MAXN];
bitset<MAXN> vis;
vector<int> g[MAXN];
struct Edge {
    int u, v;
} e[MAXN];

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

void solve() {
    cin >> n >> m;
    top = cnt = tot = 0;
    for (int i = 1; i <= m; i++)
        cin >> e[i].u >> e[i].v;
    for (int i = 1, x; i <= n; i++)
        cin >> x, pos[x] = i;
    if (m > 3 * n + 6) return cout << "NO\n", void();
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(scc, 0, sizeof(scc));
    vis.reset();
    for (int i = 1; i <= (m << 1); i++)
        g[i].clear();
    for (int i = 1; i <= m; i++) {
        auto [u1, v1] = e[i];
        if (pos[u1] > pos[v1]) swap(u1, v1);
        if (pos[u1] + 1 == pos[v1] || (pos[u1] == 1 && pos[v1] == n)) continue;
        for (int j = 1; j < i; j++) {
            auto [u2, v2] = e[j];
            if (pos[u2] > pos[v2]) swap(u2, v2);
            if (pos[u2] + 1 == pos[v2] || (pos[u2] == 1 && pos[v2] == n)) continue;
            if ((pos[u1] < pos[u2] && pos[u2] < pos[v1] && pos[v1] < pos[v2]) ||
                (pos[u2] < pos[u1] && pos[u1] < pos[v2] && pos[v2] < pos[v1])) {
                g[i].emplace_back(j + m);
                g[i + m].emplace_back(j);
                g[j].emplace_back(i + m);
                g[j + m].emplace_back(i);
            }
        }
    }
    for (int i = 1; i <= (m << 1); i++)
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= m; i++)
        if (scc[i] == scc[i + m]) return cout << "NO\n", void();
    return cout << "YES\n", void();
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) solve();

    return 0;
}