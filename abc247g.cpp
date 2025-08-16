#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 710, INF = 0x3f3f3f3f3f3f3f3f;
int n, m, s, t, cst, cnt, cur[MAXN], dis[MAXN];
bitset<MAXN> vis;

struct Edge {
    int v, w, c, id;

    Edge(int V, int W, int C, int ID) : v(V), w(W), c(C), id(ID) {}
};
vector<Edge> g[MAXN], h[MAXN];

void add(int u, int v, int w, int c) {
    int uid = g[u].size(), vid = g[v].size();
    g[u].emplace_back(v, w, c, vid);
    g[v].emplace_back(u, 0, -c, uid);
}

queue<int> q;
bool spfa() {
    memset(dis, 0x3f, sizeof(dis));
    q.emplace(s);
    dis[s] = 0, vis[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop(), vis[u] = 0;
        for (auto [v, w, c, id] : g[u]) {
            if (w && dis[v] > dis[u] + c) {
                dis[v] = dis[u] + c;
                if (!vis[v]) q.emplace(v), vis[v] = 1;
            }
        }
    }
    memset(cur, 0, sizeof(cur));
    return dis[t] ^ INF;
}

int dfs(int u, int lim) {
    if (u == t) return lim;
    vis[u] = 1;
    int res = 0;
    for (int &i = cur[u]; i < g[u].size(); i++) {
        auto [v, w, c, id] = g[u][i];
        if (!vis[v] && w && dis[v] == dis[u] + c) {
            int tmp = dfs(v, min(w, lim - res));
            if (tmp) g[u][i].w -= tmp, g[v][id].w += tmp, cst += tmp * c, res += tmp;
        }
    }
    vis[u] = 0;
    return res;
}

int dinic() {
    cst = 0;
    int res = 0, tmp;
    while (spfa())
        while (tmp = dfs(s, INF)) res += tmp;
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    n = 150;
    cin >> m;
    s = 0, t = 301;
    for (int i = 1; i <= n; i++) add(s, i, 1, 0);
    for (int i = 1; i <= n; i++) add(i + n, t, 1, 0);
    for (int i = 1, u, v, c; i <= m; i++) {
        cin >> u >> v >> c;
        add(u, v + n, 1, -c);
    }
    for (int j = 0; j <= t; j++) h[j] = g[j];
    int cnt = dinic();
    cout << cnt << '\n';
    t = 302;
    for (int i = 1; i <= cnt; i++) {
        for (int j = 0; j <= t; j++) g[j] = h[j];
        add(301, t, i, 0);
        dinic();
        cout << -cst << '\n';
    }

    return 0;
}