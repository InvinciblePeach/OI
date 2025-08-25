#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 5e5 + 10;
int n, m, ans = INT_MAX, id, dis[2][MAXN], deg[MAXN], q[MAXN], l = 1, r = 0;
multiset<int> st;
vector<int> g[MAXN], h[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        deg[v]++;
        g[u].emplace_back(v);
        h[v].emplace_back(u);
    }
    for (int i = 1; i <= n; i++)
        if (!deg[i]) q[++r] = i;
    while (l <= r) {
        int u = q[l++];
        for (auto v : g[u]) {
            if (!--deg[v]) q[++r] = v;
        }
    }
    assert(r == n);
    for (int i = 1; i <= n; i++) {
        for (auto v : g[q[i]])
        dis[0][v] = max(dis[0][v], dis[0][q[i]] + 1);
    }
    for (int i = n; i; i--) {
        for (auto v : h[q[i]])
        dis[1][v] = max(dis[1][v], dis[1][q[i]] + 1);
    }

    for (int i = 1; i <= n; i++) st.emplace(dis[1][i]);
    for (int i = 1; i <= n; i++) {
        auto &u = q[i];
        st.erase(st.find(dis[1][u]));
        for (auto v : h[u]) st.erase(st.find(dis[0][v] + dis[1][u] + 1));

        auto tmp = *st.rbegin();
        if (tmp < ans) ans = tmp, id = u;

        for (auto v : g[u]) st.emplace(dis[0][u] + dis[1][v] + 1);
        st.emplace(dis[0][u]);
    }
    cout << id << ' ' << ans << '\n';

    return 0;
}