#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

const int MAXN = 4e5 + 10, INF = 0x3f3f3f3f;
int n, m, q, k, s, tot, dis[MAXN], fa[20][MAXN];
struct Edge {
    int v, w, d;
    Edge(int V, int W, int D) : v(V), w(W), d(D) {}
};
vector<Edge> g[MAXN];

int w[MAXN << 1], mn[MAXN << 1];
vector<int> t[MAXN << 1];

namespace dijskra {
    bitset<MAXN> vis;
    priority_queue<pii, vector<pii>, greater<>> q;

    void dijskra() {
        memset(dis, 0x3f, sizeof(dis));
        q.emplace(dis[1] = 0, 1);
        vis.reset();
        while (!q.empty()) {
            auto [d, u] = q.top();
            q.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            for (auto [v, w, p] : g[u])
                if (d + w < dis[v]) q.emplace(dis[v] = d + w, v);
        }
    }
} // namespace dijskra

int newnode(int x) {
    w[++tot] = x;
    return tot;
}

namespace kruskal {
    int fa[MAXN << 1];
    struct Edge {
        int u, v, w, d;
        bool operator<(const Edge &o) const { return d > o.d; }
    } e[MAXN];
    int cnt = 0;

    int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }

    void merge(int a, int b) { fa[get(a)] = get(b); }

    void insert(int u, int v, int w, int d) { e[++cnt] = {u, v, w, d}; }

    void kruskal() {
        memset(w, 0, sizeof(w));
        tot = n;
        for (int i = 1; i <= (n << 1); i++) fa[i] = i;
        sort(e + 1, e + cnt + 1);
        for (int i = 1; i <= cnt; i++) {
            auto [u, v, w, d] = e[i];
            if (get(u) == get(v)) continue;
            int fau = get(u), fav = get(v);
            int p = newnode(d);
            t[fau].emplace_back(p);
            t[fav].emplace_back(p);
            t[p].emplace_back(fau);
            t[p].emplace_back(fav);
            fa[fau] = fa[fav] = p;
        }
    }
} // namespace kruskal

void dfs(int u) {
    if (u <= n)
        mn[u] = dis[u];
    else
        mn[u] = INF;
    for (int i = 1; i < 20; i++) fa[i][u] = fa[i - 1][fa[i - 1][u]];
    for (auto v : t[u]) {
        if (v == fa[0][u]) continue;
        fa[0][v] = u;
        // cerr << u << ' ' << v << '\n';
        dfs(v);
        mn[u] = min(mn[u], mn[v]);
    }
}

void solve() {
    memset(mn, 0, sizeof(mn));
    memset(fa, 0, sizeof(fa));
    cin >> n >> m;
    kruskal::cnt = 0;
    for (int i = 1, u, v, w, d; i <= m; i++) {
        cin >> u >> v >> w >> d;
        g[u].emplace_back(v, w, d);
        g[v].emplace_back(u, w, d);
        kruskal::insert(u, v, w, d);
    }
    dijskra::dijskra();
    kruskal::kruskal();
    dfs(tot);
    // for (int i = 1; i <= tot; i++) cerr << mn[i] << " \n"[i == tot];
    cin >> q >> k >> s;
    int ans = 0;
    w[0] = -INF;
    while (q-- > 0) {
        static int u, p;
        cin >> u >> p;
        u = (u + k * ans - 1) % n + 1;
        p = (p + k * ans) % (s + 1);
        for (int i = 19; ~i; i--) {
            // cerr << fa[i][u] << ':' << w[fa[i][u]] << '\n';
            if (w[fa[i][u]] > p) u = fa[i][u];
        }
        // cerr << u << '\n';
        cout << (ans = mn[u]) << '\n';
    }
    for (int i = 1; i <= n; i++) g[i].clear();
    for (int i = 1; i <= tot; i++) t[i].clear();
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T-- > 0) {
        solve();
    }
    return 0;
}