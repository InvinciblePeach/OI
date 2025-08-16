#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 2e5 + 10, S = 50;
int n, m, q, deg[MAXN], ans[MAXN], vis[MAXN];
vector<int> g[MAXN];
vector<pii> qry[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> q;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v, deg[u]++, deg[v]++;
        g[u].emplace_back(v), g[v].emplace_back(u);
    }
    for (int i = 1, u, v; i <= q; i++) {
        cin >> u >> v;
        ans[i] = deg[u];
        if (deg[u] < deg[v]) swap(u, v);
        qry[u].emplace_back(v, i);
    }

    for (int u = 1; u <= n; u++) {
        sort(qry[u].begin(), qry[u].end());
        for (auto v : g[u]) vis[v] = u;
        int lst = 0, res = 0;
        for (auto [v, id] : qry[u]) {
            if (v == lst) {
                ans[id] -= res;
                continue;
            }
            res = vis[v] == u;
            for (auto w : g[v]) res += vis[w] == u;
            ans[id] -= res;
            lst = v;
        }
    }
    for (int i = 1; i <= q; i++) cout << ans[i] << '\n';

    return 0;
}