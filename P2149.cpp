#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef priority_queue<pii, vector<pii>, greater<>> pqpii;

const int MAXN = 1510;
int n, m, ans, len[MAXN], dis[4][MAXN], deg[MAXN], s1, t1, s2, t2;

struct Edge {
    int v, w;
    Edge() {}
    Edge(int V, int W) : v(V), w(W) {}
};
vector<Edge> g[MAXN], h[MAXN];

void dijskra(int s, int id) {
    static pqpii q;
    static bitset<MAXN> vis;
    auto dis = ::dis[id];
    pqpii().swap(q), vis.reset();
    q.emplace(dis[s] = 0, s);

    while (q.size()) {
        auto [d, u] = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;

        for (auto [v, w] : g[u])
            if (dis[v] > d + w) q.emplace(dis[v] = d + w, v);
    }
}

void topu() {
    static queue<int> q;
    queue<int>().swap(q);
    for (int i = 1; i <= n; i++) if (!deg[i]) q.emplace(i);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        // cerr << u << '\n';

        for (auto [v, w] : h[u]) {
            len[v] = max(len[v], len[u] + w);
            if (!--deg[v]) q.emplace(v);
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    cin >> s1 >> t1 >> s2 >> t2;
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    memset(dis, 0x3f, sizeof(dis));

    dijskra(s1, 0);
    dijskra(t1, 1);
    dijskra(s2, 2);
    dijskra(t2, 3);

    for (int u = 1; u <= n; u++)
        for (auto [v, w] : g[u])
            if (dis[0][u] + w + dis[1][v] == dis[0][t1] && dis[2][u] + w + dis[3][v] == dis[2][t2])
                h[u].emplace_back(v, w), deg[v]++;
    topu();
    for (int i = 1; i <= n; i++) ans = max(ans, len[i]);

    for (int i = 1; i <= n; i++) h[i].clear();
    memset(deg, 0, sizeof(deg)), memset(len, 0, sizeof(len));
    
    for (int u = 1; u <= n; u++)
        for (auto [v, w] : g[u])
            if (dis[0][u] + w + dis[1][v] == dis[0][t1] && dis[3][u] + w + dis[2][v] == dis[2][t2])
                h[u].emplace_back(v, w), deg[v]++;
    topu();
    for (int i = 1; i <= n; i++) ans = max(ans, len[i]);

    cout << ans << '\n';

    return 0;
}