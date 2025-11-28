#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e5 + 10, INF = 0x3f3f3f3f;
int T, n, m, cnt[MAXN], dis[MAXN];
bitset<MAXN> vis;
struct Edge {
    int v, w;
    Edge(int V, int W) : v(V), w(W) {}
};
vector<Edge> g[MAXN];

bool spfa() {
    queue<int> q;
    dis[1] = 0;
    q.emplace(1);
    vis[1] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (auto [v, w] : g[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (!vis[v]) {
                    if (++cnt[v] >= n) return true;
                    vis[v] = 1;
                    q.emplace(v);
                }
            }
        }
    }
    return false;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T-- > 0) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) g[i].clear(), cnt[i] = vis[i] = 0, dis[i] = INF;
        for (int i = 1, u, v, w; i <= m; i++) {
            cin >> u >> v >> w;
            g[u].emplace_back(v, w);
            if (w >= 0) g[v].emplace_back(u, w);
        }
        cout << (spfa() ? "YES\n" : "NO\n");
    }

    return 0;
}