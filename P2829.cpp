#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef priority_queue<pii, vector<pii>, greater<>> pqpii;

const int MAXN = 5010, INF = 0x3f3f3f3f;
int n, m, k, ans = INF, d[MAXN], dis1[MAXN], dis2[MAXN];
set<pii> g[MAXN];
pii e[MAXN];

void dijskra(int s, int *dis) {
    static pqpii q;
    static bitset<MAXN> vis;
    pqpii().swap(q), vis.reset();
    q.emplace(dis[s] = 0, s);

    while (!q.empty()) {
        auto [t, u] = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;

        for (auto [v, w] : g[u])
            if (d[v] >= k && dis[v] > t + w) q.emplace(dis[v] = t + w, v);
    }
    // for (int i = 1; i <= n; i++) cerr << dis[i] << " \n"[i == n];
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> k;
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        g[u].emplace(v, w), g[v].emplace(u, w);
    }

    for (int i = 2; i < n; i++) {
        static bitset<MAXN> vis;
        vis.reset();
        for (auto [v, w] : g[i]) {
            if (!vis[v]) {
                vis[v] = 1;
                d[i]++;
            }
        }
    }
    d[1] = INF;
    d[n] = INF;
    memset(dis1, 0x3f, sizeof(dis1));
    memset(dis2, 0x3f, sizeof(dis2));
    dijskra(1, dis1), dijskra(n, dis2);
    for (int u = 1; u <= n; u++) {
        if (u != 1 && u != n && g[u].size() < k) continue;
        for (auto [v, w] : g[u]) {
            if (d[v] >= k && dis1[u] + w + dis2[v] > dis1[n])
                ans = min(ans, dis1[u] + w + dis2[v]);
        }
    }
    cout << (ans >= INF ? -1 : ans) << '\n';

    return 0;
}