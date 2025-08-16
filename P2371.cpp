#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 5e5 + 10;
int n, l, r, ans, a[MAXN], dis[MAXN];

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

    cin >> n >> l >> r;
    l--;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 0; i < a[1]; i++)
        for (int j = 2; j <= n; j++)
            g[i].emplace_back((i + a[j]) % a[1], a[j]);
    dijskra();
    for (int i = 0; i < a[1]; i++) {
        if (r >= dis[i]) ans += (r - dis[i]) / a[1] + 1;
        if (l >= dis[i]) ans -= (l - dis[i]) / a[1] + 1;
    }
    cout << ans << '\n';

    return 0;
}