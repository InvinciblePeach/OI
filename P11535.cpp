#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<ll, int>;

const int MAXN = 2e5 + 10;
int n, m, a[MAXN];
ll ans = LLONG_MAX, dis1[MAXN], dis2[MAXN];
priority_queue<pii, vector<pii>, greater<>> q;
bitset<MAXN> vis;
vector<int> g[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    memset(dis1, 0x3f, sizeof(dis1));
    memset(dis2, 0x3f, sizeof(dis2));
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    q.emplace(dis1[1] = 0, 1);
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int v : g[u])
            if (dis1[v] > d + max(1ll, a[v] - d)) q.emplace(dis1[v] = d + max(1ll, a[v] - d), v);
    }
    vis.reset();
    q.emplace(dis2[n] = 0, n);
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int v : g[u])
            if (dis2[v] > d + max(1ll, a[v] - d)) q.emplace(dis2[v] = d + max(1ll, a[v] - d), v);
    }
    for (int i = 1; i <= n; i++) {
        ans = min(ans, dis1[i] + dis2[i] + abs(dis1[i] - dis2[i]));
        for (int j : g[i])
            if (dis1[i] == dis2[j]) ans = min(ans, dis1[i] + dis2[j] + 1);
    }
    cout << ans << '\n';

    return 0;
}