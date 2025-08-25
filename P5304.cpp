#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef priority_queue<pii, vector<pii>, greater<>> pqpii;

const int MAXN = 1e5 + 10, MAXM = 5e5 + 10;
int T, n, m, k, ans, dis[MAXN], pos[MAXN];

struct Graph {
    int cnt, hd[MAXN];

    void clear() { memset(this, 0, sizeof(Graph)); }

    struct Edge {
        int nxt, v, w;
    } g[MAXM];

    constexpr auto operator[](int x) { return g[x]; }

    constexpr void add(int u, int v, int w) { g[++cnt] = {hd[u], v, w}, hd[u] = cnt; }
} g, h;

int dijskra(int s, int t) {
    static pqpii pq;
    static bitset<MAXN> vis;
    pqpii().swap(pq), vis.reset();
    memset(dis, 0x3f, sizeof(dis));
    pq.emplace(dis[s] = 0, s);
    while (pq.size()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (vis[u]) continue;
        vis[u] = 1;

        for (int i = g.hd[u]; i; i = g[i].nxt) {
            auto v = g[i].v, w = g[i].w;
            if (dis[v] > d + w) pq.emplace(dis[v] = d + w, v);
        }
    }
    return dis[t];
}

void solve() {
    static int s, t;
    cin >> n >> m >> k;
    s = 0, t = n + 1, ans = LLONG_MAX, h.clear();
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        h.add(u, v, w);
    }
    for (int i = 1; i <= k; i++) cin >> pos[i];

    for (int i = 0; i < 20; i++) {
        g = h;
        for (int j = 1; j <= k; j++) {
            if (j >> i & 1) g.add(s, pos[j], 0);
            else g.add(pos[j], t, 0);
        }
        ans = min(ans, dijskra(s, t));

        g = h;
        for (int j = 1; j <= k; j++) {
            if (j >> i & 1) g.add(pos[j], t, 0);
            else g.add(s, pos[j], 0);
        }
        ans = min(ans, dijskra(s, t));
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) solve();

    return 0;
}