#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 5010, MAXM = 1e6 + 10;
int n, m, cnt, ans, fa[MAXN], from[MAXN], sec[MAXN], rt[MAXN];
bitset<MAXN> vis;
double E, dis[MAXN];

struct Edge {
    int v;
    double w;
    int id;

    Edge() {}
    Edge(int V, double W, int Id) : v(V), w(W), id(Id) {}
};
vector<Edge> g[MAXN], h[MAXN];

struct Node {
    int lc, rc;
    double sum;
    int dep, fa;
} t[MAXM];
int tot;

int nw(int f, double val) {
    t[++tot] = {0, 0, val, 0, f};
    return tot;
}

int merge(int x, int y) {
    if (!x || !y) return x | y;
    if (t[x].sum > t[y].sum) swap(x, y);
    int p = ++tot;
    t[p] = t[x];
    t[p].rc = merge(t[p].rc, y);
    if (t[t[p].lc].dep < t[t[p].rc].dep) swap(t[p].lc, t[p].rc);
    t[p].dep = t[t[p].rc].dep + 1;
    return p;
}

void dijkstra() {
    for (int i = 1; i <= n; i++) dis[i] = INFINITY;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;
    pq.emplace(dis[n] = 0, n);
    while (!pq.empty()) {
        auto [c, u] = pq.top();
        pq.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto [v, w, id] : h[u]) {
            if (dis[v] > c + w) pq.emplace(dis[v] = c + w, v), from[v] = id, fa[v] = u;
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> E;
    for (int i = 1; i <= m; i++) {
        static int u, v;
        static double w;
        cin >> u >> v >> w;
        if (u == n) {
            i--, m--;
            continue;
        }
        g[u].emplace_back(v, w, ++cnt);
        h[v].emplace_back(u, w, cnt);
    }
    for (int i = 1; i <= n; i++) sec[i] = i;
    dijkstra();
    sort(sec + 1, sec + 1 + n, [](int a, int b) -> bool { return dis[a] < dis[b]; });
    t[0].dep = -1;

    for (int i = 1; i <= n; i++) {
        int u = sec[i];
        for (auto [v, w, id] : g[u]) {
            if (id == from[u]) continue;
            rt[u] = merge(rt[u], nw(v, w - dis[u] + dis[v]));
        }
        rt[u] = merge(rt[u], rt[fa[u]]);
    }

    E -= dis[1], ans = 1;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;
    pq.emplace(t[rt[1]].sum, rt[1]);
    while (!pq.empty()) {
        auto [c, v] = pq.top();
        pq.pop();
        if (E < c + dis[1]) return cout << ans << '\n', 0;
        E -= c + dis[1], ans++;
        if (t[v].lc) pq.emplace(c - t[v].sum + t[t[v].lc].sum, t[v].lc);
        if (t[v].rc) pq.emplace(c - t[v].sum + t[t[v].rc].sum, t[v].rc);
        if (rt[t[v].fa]) pq.emplace(c + t[rt[t[v].fa]].sum, rt[t[v].fa]);
    }

    return cout << ans << '\n', 0;
}