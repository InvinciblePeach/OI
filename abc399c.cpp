#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int n, m, ans, t;
vector<int> g[MAXN];
int vis[MAXN];

void dfs(int u, int fa) {
    vis[u] = ++t;
    for (auto v : g[u]) {
        if (vis[v]) {
            if (v != fa) ans += vis[v] < vis[u];
            continue;
        }
        dfs(v, u);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        g[u].emplace_back(v), g[v].emplace_back(u);
    }
    for (int i = 1; i <= n; i++)
        if (!vis[i]) dfs(i, 0);
    cout << ans << '\n';

    return 0;
}