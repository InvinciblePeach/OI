#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<double, int> pdi;

const int MAXN = 6e5 + 10;
int n, m, deg[MAXN], cnt[MAXN];
double dp[MAXN], sum[MAXN];
vector<int> g[MAXN];
bitset<MAXN> vis;
priority_queue<pdi, vector<pdi>, greater<>> q;

void dijkstra() {
    q.emplace(0, n);
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();

        if (vis[u]) continue;
        vis[u] = 1;

        for (auto v : g[u]) {
            if (vis[v]) continue;
            cnt[v]++, sum[v] += dp[u];
            q.emplace(dp[v] = (g[v].size() + sum[v]) / cnt[v], v);
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dijkstra();
    printf("%.7lf\n", dp[1]);

    return 0;
}