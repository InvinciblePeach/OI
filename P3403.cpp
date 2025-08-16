#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 1e5 + 10;
int h, x, y, z, ans, dis[MAXN];
struct Edge {
    int v, w;
    Edge(int V, int W) : v(V), w(W) {}
};
vector<Edge> g[MAXN];
bitset<MAXN> vis;

void dijskra() {
    priority_queue<pii, vector<pii>, greater<>> q;
    memset(dis, 0x3f, sizeof(dis));
    q.emplace(dis[0] = 0, 0);
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;

        for (auto [v, w] : g[u])
            if (dis[v] > d + w) q.emplace(dis[v] = d + w, v);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> h >> x >> y >> z;
    h--;
    for (int i = 0; i < x; i++)
        g[i].emplace_back((i + y) % x, y);
    for (int i = 0; i < x; i++)
        g[i].emplace_back((i + z) % x, z);
    dijskra();
    for (int i = 0; i < x; i++)
        if (h >= dis[i]) ans += (h - dis[i]) / x + 1;
    cout << ans << '\n';

    return 0;
}