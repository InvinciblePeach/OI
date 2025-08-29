#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
int n, m, ans, deg[MAXN], cnt[MAXN], dis[MAXN];
struct Edge {
    int v, w;
    Edge(int V, int W) : v(V), w(W) {}
};
vector<Edge> g[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, op, u, v; i <= m; i++) {
        cin >> op >> u >> v;
        if (op == 1) g[u].emplace_back(v, 0), g[v].emplace_back(u, 0), deg[u]++, deg[v]++;
        if (op == 2) {
            if (u == v) {
                cout << "-1\n";
                return 0;
            }
            g[u].emplace_back(v, 1), deg[v]++;
        }
        if (op == 3) g[v].emplace_back(u, 0), deg[u]++;
        if (op == 4) {
            if (u == v) {
                cout << "-1\n";
                return 0;
            }
            g[v].emplace_back(u, 1), deg[u]++;
        }
        if (op == 5) g[u].emplace_back(v, 0), deg[v]++;
    }

    bitset<MAXN> vis;
    queue<int> q;
    for (int i = n; i; i--)
        g[0].emplace_back(i, 1), deg[i]++;
    q.emplace(0);
    vis[0] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (auto [v, w] : g[u]) {
            if (dis[v] < dis[u] + w) {
                dis[v] = dis[u] + w;
                if (!vis[v]) {
                    q.emplace(v), vis[v] = 1;
                    if (++cnt[v] > n) {
                        cout << "-1\n";
                        return 0;
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
        ans += dis[i];
    cout << ans << '\n';

    return 0;
}