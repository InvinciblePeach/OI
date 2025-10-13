#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e5 + 10;
int n, m, ans, deg[MAXN], vis[MAXN];
vector<int> g[MAXN];

struct Edge {
    int u, v;
} e[MAXN << 1];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> e[i].u >> e[i].v;
        deg[e[i].u]++, deg[e[i].v]++;
    }
    for (int i = 1; i <= m; i++) {
        auto [u, v] = e[i];
        if (deg[u] > deg[v]) swap(u, v);
        if (deg[u] == deg[v] && u > v) swap(u, v);
        g[u].emplace_back(v);
    }
    for (int i = 1; i <= n; i++) {
        for (auto v : g[i]) vis[v] = i;
        for (auto v : g[i])
            for (auto w : g[v])
                if (vis[w] == i) ans++;
    }
    cout << ans << '\n';

    return 0;
}