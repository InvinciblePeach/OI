#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e5 + 10;
int n, m;
double dp[MAXN];
vector<pii> g[MAXN];

void dfs(int u) {
    if (dp[u] != 0) return;
    for (auto [v, w] : g[u]) {
        dfs(v);
        dp[u] += w + dp[v];
    }
    // cerr << u << ' ' << dp[u] << '\n';
    if (!g[u].empty()) dp[u] /= double(g[u].size());
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i++) cin >> u >> v >> w, g[u].emplace_back(v, w);
    dfs(1);
    // for (int i = 1; i <= n; i++) cerr << dp[i] << " \n"[i == n];
    printf("%.2lf\n", dp[1]);

    return 0;
}