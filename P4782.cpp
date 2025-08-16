#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e6 + 10;
int n, m;
int tot, cnt, top, st[MAXN], dfn[MAXN], low[MAXN], scc[MAXN];
bitset<MAXN> vis;
vector<int> g[MAXN];

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

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, a, b, x, y; i <= m; i++) {
        cin >> a >> x >> b >> y;
        if (x && y) {
            g[a + n].emplace_back(b);
            g[b + n].emplace_back(a);
        } else if (!x && y) {
            g[a].emplace_back(b);
            g[b + n].emplace_back(a + n);
        } else if (x && !y) {
            g[a + n].emplace_back(b + n);
            g[b].emplace_back(a);
        } else if (!x && !y) {
            g[a].emplace_back(b + n);
            g[b].emplace_back(a + n);
        }
    }
    for (int i = 1; i <= (n << 1); i++)
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n; i++)
        if (scc[i] == scc[i + n])
            return cout << "IMPOSSIBLE\n", 0;
    cout << "POSSIBLE\n";
    for (int i = 1; i <= n; i++)
        cout << (scc[i] < scc[i + n]) << " \n"[i == n];

    return 0;
}