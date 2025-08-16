#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 1e5 + 10;
int n, k, tot, ans, dep[MAXN], dis[MAXN], fa[MAXN], son[MAXN], top[MAXN];
priority_queue<int> q;
struct Edge {
    int v, w;
    Edge(int V, int W) : v(V), w(W) {}
};
vector<Edge> g[MAXN];

void dfs1(int u) {
    for (auto p : g[u]) {
        int v = p.v, w = p.w;
        if (v == fa[u]) continue;
        fa[v] = u, dep[v] = dep[u] + w;
        dfs1(v);
        if (dis[v] + w > dis[u]) son[u] = v, dis[u] = dis[v] + w;
    }
}

void dfs2(int u, int top) {
    ::top[u] = top;
    if (!son[u]) q.emplace((dep[u] - dep[fa[top]]) - dep[fa[top]]), cerr << u << '\n';
    if (son[u]) dfs2(son[u], top);
    for (auto p : g[u]) {
        int v = p.v, w = p.w;
        if (v == son[u] || v == fa[u]) continue;
        dfs2(v, v);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> k;
    for (int i = 1, u, v, w; i < n; i++) {
        cin >> u >> v >> w;
        g[u].emplace_back(v, w), g[v].emplace_back(u, w);
        ans += (w << 1);
    }
    dfs1(1), dfs2(1, 1);
    // for (int i = 1; i <= n; i++) cerr << top[i] << " \n"[i == n];
    // cerr << ans << '\n';
    while (!q.empty() && k-- > 0 && q.top() > 0) {
        // cerr << k << ' ' << q.top() << '\n';
        ans -= q.top();
        q.pop();
    }
    cout << ans << '\n';
    return 0;
}