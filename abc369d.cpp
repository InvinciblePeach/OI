#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 15;
int n, m, ans = LLONG_MAX;
bitset<MAXN> vis;

struct Edge {
    int v, w;

    Edge() {}
    Edge(const int &V, const int &W) : v(V), w(W) {}
};
vector<Edge> g[MAXN];

void dfs(int u, int res) {
    if (u == n) {
        ans = min(ans, res);
        return;
    }
    for (auto e : g[u]) {
        auto [v, w] = e;
        if (vis[v]) continue;
        vis[v] = 1;
        dfs(v, res ^ w);
        vis[v] = 0;
    }
}


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    vis[1] = 1;
    dfs(1, 0);
    cout << ans << '\n';

    return 0;
}