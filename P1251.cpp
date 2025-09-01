#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 4e3 + 10, INF = 0x3f3f3f3f3f3f3f3f;
int n, s, t, a, b, c, e, d;
struct Edge {
    int v, w, c, id;
    Edge(int V, int W, int C, int ID) : v(V), w(W), c(C), id(ID) {}
};
vector<Edge> g[MAXN];

void add(int u, int v, int w, int c) {
    int uid = g[u].size(), vid = g[v].size();
    g[u].emplace_back(v, w, c, vid);
    g[v].emplace_back(u, 0, -c, uid);
}

int dis[MAXN], cur[MAXN];
bitset<MAXN> vis;
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

int cst = 0;
int dfs(int u, int lim) {
    if (u == t) return lim;
    vis[u] = 1;
    int res = 0;
    
    for (int &i = cur[u]; i < g[u].size(); i++) {
        auto [v, w, c, id] = g[u][i];
        if (!vis[v] && w && dis[v] == dis[u] + c) {
            int tmp = dfs(v, min(lim - res, w));
            g[u][i].w -= tmp, g[v][id].w += tmp;
            res += tmp, cst += tmp * c;
        }
    }
    vis[u] = 0;
    return res;
}

int dinic() {
    int tmp = 0, res = 0;
    while (spfa()) {
        while (tmp = dfs(s, INF)) res += tmp;
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    s = 0, t = (n + 1) << 1;
    for (int i = 1, p; i <= n; i++) {
        cin >> p;
        add(i << 1, t, p, 0);
        add(s, i << 1 | 1, p, 0);
    }
    cin >> a >> b >> c >> d >> e;
    for (int i = 1; i <= n; i++) {
        add(s, i << 1, INF, a);
        if (i + 1 <= n) add(i << 1 | 1, (i + 1) << 1 | 1, INF, 0);
        if (i + b <= n) add(i << 1 | 1, (i + b) << 1, INF, c);
        if (i + d <= n) add(i << 1 | 1, (i + d) << 1, INF, e);
    }
    dinic();
    cout << cst << '\n';

    return 0;
}