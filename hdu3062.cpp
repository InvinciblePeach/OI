#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 2010;
int n, m, tot, cnt, scc[MAXN], id[MAXN], low[MAXN], top, st[MAXN];
bitset<MAXN> vis;
vector<int> g[MAXN];

void tarjan(int u) {
    id[u] = low[u] = ++tot;
    st[++top] = u, vis[u] = 1;
    for (auto v : g[u]) {
        if (!id[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v]) low[u] = min(low[u], id[v]);
    }
    if (id[u] == low[u]) {
        vis[u] = 0, scc[u] = ++cnt;
        while (st[top] != u)
            vis[st[top]] = 0, scc[st[top]] = cnt, top--;
        top--;
    }
}

void solve() {
    memset(id, 0, sizeof(id));
    memset(low, 0, sizeof(low));
    memset(scc, 0, sizeof(scc));
    memset(st, 0, sizeof(st));
    vis.reset();
    tot = cnt = top = 0;
    for (int i = 0; i < (n << 1); i++) g[i].clear();
    for (int i = 1, a, b, x, y; i <= m; i++) {
        cin >> a >> b >> x >> y;
        g[2 * a + x].emplace_back(2 * b + 1 - y);
        g[2 * b + y].emplace_back(2 * a + 1 - x);
    }
    for (int i = 0; i < (n << 1); i++)
        if (!id[i]) tarjan(i);
    for (int i = 0; i < n; i++) {
        if (scc[i << 1] == scc[i << 1 | 1]) return cout << "NO\n", void();
    } 
    cout << "YES\n";
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    while (cin >> n >> m) solve();

    return 0;
}