#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 4e5 + 10;
int n, m, dis[MAXN];
bitset<MAXN> vis;

struct Edge {
    int v, w;

    Edge(int V, int W) : v(V), w(W) {}

    bool operator<(const Edge &o) const { return w < o.w; }
};
vector<pii> g[MAXN];
vector<Edge> h[MAXN];
priority_queue<pii, vector<pii>, greater<>> q;

void dijkstra() {
    memset(dis, 0x3f, sizeof(dis));
    q.emplace(dis[0] = 0, 0);
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();

        if (vis[u]) continue;
        vis[u] = 1;

        for (auto [v, w] : h[u])
            if (dis[v] > d + w) q.emplace(dis[v] = d + w, v);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        g[u].emplace_back(w, i);
        g[v].emplace_back(w, i);
    }
    for (int i = 2; i < n; i++) {
        sort(g[i].begin(), g[i].end());
        for (int j = 1; j < g[i].size(); j++) {
            h[g[i][j].second].emplace_back(g[i][j - 1].second, abs(g[i][j].first - g[i][j - 1].first));
            h[g[i][j - 1].second].emplace_back(g[i][j].second, abs(g[i][j].first - g[i][j - 1].first));
        }
    }
    for (auto [w, id] : g[1])
        h[0].emplace_back(id, w);
    for (auto [w, id] : g[n])
        h[id].emplace_back(m + 1, 0);
    dijkstra();
    cout << dis[m + 1] << '\n';

    return 0;
}