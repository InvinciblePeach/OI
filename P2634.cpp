#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 2e4 + 10;
int n, S, rt, ans, dis[MAXN], siz[MAXN], mx[MAXN], bsk[3];
int st[MAXN], tot;
bitset<MAXN> vis;

struct Edge {
    int v, w;

    Edge() {}
    Edge(const int &V, const int &W) : v(V), w(W) {}
};
vector<Edge> g[MAXN];

void find(int u, int fa) {
    siz[u] = 1, mx[u] = 0;
    for (auto e : g[u]) {
        auto [v, w] = e;
        if (vis[v] || v == fa) continue;
        find(v, u);
        siz[u] += siz[v], mx[u] = max(mx[u], siz[v]);
    }
    mx[u] = max(mx[u], S - siz[u]);
    if (mx[u] < mx[rt]) rt = u;
}

void dfs(int u, int fa) {
    st[++tot] = dis[u];
    for (auto e : g[u]) {
        auto [v, w] = e;
        if (vis[v] || v == fa) continue;
        dis[v] = (dis[u] + w) % 3;
        dfs(v, u);
    }
}

void calc(int u) {
    bsk[0] = 1;
    for (auto e : g[u]) {
        auto [v, w] = e;
        if (vis[v]) continue;
        dis[v] = w % 3, tot = 0;
        dfs(v, u);

        for (int i = 1; i <= tot; i++)
            ans += bsk[(3 - st[i]) % 3] << 1;
        for (int i = 1; i <= tot; i++)
            bsk[st[i]]++;
    }
    memset(bsk, 0, sizeof(bsk));
}

void solve(int u) {
    vis[u] = 1, calc(u);
    for (auto e : g[u]) {
        auto [v, w] = e;
        if (vis[v]) continue;
        find(v, u);
        S = siz[v], mx[rt = 0] = INT_MAX;
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
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    ans = n;
    solve(1);
    int p = n * n, tmp;
    while ((tmp = __gcd(ans, p)) > 1)
        ans /= tmp, p /= tmp;
    cout << ans << '/' << p << '\n';
    return 0;
}