#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 5e4 + 10;
int n, m, f[MAXN], cnt, x;

struct Edge {
    int v, w;
    Edge() {}
    Edge(int V, int W): v(V), w(W) {}
};
vector<Edge> g[MAXN];
int p[MAXN], del[MAXN], ed;

void dfs(int u, int fa) {
    for (auto [v, w] : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
    }

    ed = 0;
    for (auto [v, w] : g[u]) {
        if (v == fa) continue;
        p[++ed] = f[v] + w;
    }
    sort(p + 1, p + ed + 1);
    while (ed && p[ed] >= x) ed--, cnt++;
    for (int i = 1; i <= ed; i++) {
        if (del[i] == u) continue;
        int j = lower_bound(p + i + 1, p + 1 + ed, x - p[i]) - p;
        while (j <= ed && del[j] == u) j++;
        if (j <= ed) cnt++, del[j] = del[i] = u;
    }

    f[u] = 0;
    for (int i = 1; i <= ed; i++)
        if (del[i] != u) f[u] = max(f[u], p[i]);
}

bool check() {
    memset(del, 0, sizeof(del));
    cnt = 0;
    dfs(1, 1);
    return cnt >= m;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, u, v, w; i < n; i++) {
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    
    int l = 1, r = 1e9;
    while (l < r) {
        x = (l + r + 1) >> 1;
        if (check()) l = x;
        else r = x - 1;
    }
    cout << l << '\n';

    return 0;
}