#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 1e5 + 10;
int n, ans, x[MAXN];

struct Edge {
    int v, w;

    Edge() {}
    Edge(int V, int W) : v(V), w(W) {}
};
vector<Edge> g[MAXN];


int dfs(int u, int fa) {
    int sum = x[u];
    for (auto [v, w] : g[u]) {
        if (v == fa) continue;
        int tmp = dfs(v, u);
        ans += abs(tmp) * w;
        sum += tmp;
    }
    return sum;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> x[i];
    for (int i = 1; i < n; i++) {
        static int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    dfs(1, 1);
    cout << ans << "\n";
    return 0;
}