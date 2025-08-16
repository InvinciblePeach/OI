#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 1010;
int n, m, dis[MAXN], b[15];
bitset<MAXN> vis;

struct Edge {
    int v, w;

    Edge() {}
    Edge(int V, int W) : v(V), w(W) {}
};
vector<Edge> g[MAXN];

void insert(int x) {
    for (int i = 14; ~i; i--) {
        if (!(x >> i & 1)) continue;
        if (b[i]) x ^= b[i];
        else {
            b[i] = x;
            break;
        }
    }
}

int query(int x) {
    for (int i = 14; ~i; i--)
        x = min(x, x ^ b[i]);
    return x;
}

void bfs(int s) {
    queue<int> q;
    q.push(s);
    dis[s] = 0, vis[s] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, w] : g[u]) {
            if (!vis[v]) {
                vis[v] = 1, dis[v] = dis[u] ^ w;
                q.push(v);
            } else insert(dis[u] ^ w ^ dis[v]);
        }
    }
}

signed main() {
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
    }

    memset(dis, -1, sizeof(dis));
    bfs(1);

    if (!vis[n]) cout << -1 << '\n';
    else cout << query(dis[n]) << '\n';

    return 0;
}