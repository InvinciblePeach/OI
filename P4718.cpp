#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 4e4 + 10;
int n, k, ans, rt, S;
int mx[MAXN], dis[MAXN], siz[MAXN], rev[MAXN], tot;
bitset<MAXN> vis;

struct Edge {
    int v, w;

    Edge() {}
    Edge(int V, int W) : v(V), w(W) {}
};
vector<Edge> g[MAXN];

void find(int u, int fa) {
    siz[u] = 1, mx[u] = 0;
    for (auto [v, w] : g[u]) {
        if (v == fa || vis[v]) continue;
        find(v, u);
        siz[u] += siz[v], mx[u] = max(mx[u], siz[v]);
    }
    mx[u] = max(mx[u], S - siz[u]);
    if (mx[u] < mx[rt]) rt = u;
}

void dfs(int u, int fa) {
    rev[++tot] = dis[u];
    for (auto [v, w] : g[u]) {
        if (v == fa || vis[v]) continue;
        dis[v] = dis[u] + w;
        dfs(v, u);
    }
}

int calc(int u, int w) {
    tot = 0, dis[u] = w, dfs(u, u);
    sort(rev + 1, rev + 1 + tot);
    int res = 0;
    for (int l = 1, r = tot; l <= r; r--)
        while (l <= r && rev[l] + rev[r] <= k) res += r - l++;
    return res;
}

void solve(int u) {
    vis[u] = 1, ans += calc(u, 0);
    for (auto [v, w] : g[u]) {
        if (vis[v]) continue;
        ans -= calc(v, w);
        S = siz[v], mx[0] = S, rt = 0;
        find(v, u);
        solve(rt);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1, u, v, w; i < n; i++) {
        cin >> u >> v >> w;
        g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    }
    cin >> k;
    S = mx[0] = n, find(1, 1), solve(rt);
    cout << ans << '\n';

    return 0;
}