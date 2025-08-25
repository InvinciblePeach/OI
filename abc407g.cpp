#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 2010, INF = 0x7f7f7f7f7f7f7f7f;
int n, m, a[MAXN][MAXN], sum, s, t, w;
int cst, dis[MAXN], cur[MAXN], ans = INF;
bitset<MAXN> vis;
int num(int i, int j) { return (i - 1) * m + j; }

struct Edge {
    int v, w, c, id;

    Edge() {}
    Edge(int V, int W, int C, int ID) : v(V), w(W), c(C), id(ID) {}
};
vector<Edge> g[MAXN];

void add(int u, int v, int w, int c) {
    int uid = g[u].size(), vid = g[v].size();
    g[u].emplace_back(v, w, c, vid);
    g[v].emplace_back(u, 0, -c, uid);
}

bool spfa() {
    for (int i = s; i <= t; i++) dis[i] = 1e18;
    queue<int> q;
    q.emplace(s),
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
    return dis[t] != 1e18;
}

int dfs(int u, int lim) {
    if (u == t) return lim;
    vis[u] = 1;
    int res = 0;

    for (int i = cur[u]; i < g[u].size(); i++) {
        cur[u] = i;
        auto [v, w, c, id] = g[u][i];
        if (!vis[v] && w && dis[v] == dis[u] + c) {
            int tmp = dfs(v, min(w, lim - res));
            if (tmp) g[u][i].w -= tmp, g[v][id].w += tmp, cst += tmp * c, res += tmp;
        }
    }
    vis[u] = 0;
    return res;
}

int mcmf() {
    int res = 0, tmp;
    while (spfa())
        while (tmp = dfs(s, INF))
            res += tmp, ans = min(ans, cst);
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    s = 0, w = n * m + 1, t = w + 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j], sum += a[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if ((i ^ j) & 1) add(num(i, j), t, 1, 0), add(w, num(i, j), 1, 0);
            else add(s, num(i, j), 1, 0), add(num(i, j), w, 1, 0);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < m; j++)
            add(num(i, j + ((i ^ j) & 1)), num(i, j + !((i ^ j) & 1)), 1, a[i][j] + a[i][j + 1]);
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= m; j++)
            add(num(i + ((i ^ j) & 1), j), num(i + !((i ^ j) & 1), j), 1, a[i][j] + a[i + 1][j]);
    mcmf();
    cout << sum - cst << '\n';

    return 0;
}