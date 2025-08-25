#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

const int MAXN = 110;
const ld eps = 1e-8;
int n, m, d[MAXN];
ld ans, a[MAXN][MAXN];

struct Edge {
    int v, w;
    Edge() {}
    Edge(int V, int W) : v(V), w(W) {}
};
vector<Edge> g[MAXN];

void gauss() {
    for (int i = 1; i <= n; i++) {
        int nw = i;
        for (int j = i + 1; j <= n; j++) {
            if (fabs(a[j][j]) > eps) continue;
            if (fabs(a[j][i]) > fabs(a[nw][i])) nw = j;
        }
        if (fabs(a[nw][i]) < eps) continue;
        swap(a[i], a[nw]);
        ld div = a[i][i];
        for (int j = 1; j <= n + 1; j++) a[i][j] /= div;
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            div = a[j][i];
            for (int k = 1; k <= n + 1; k++)
                a[j][k] -= div * a[i][k];
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i ++) {
        cin >> u >> v >> w;
        if (u == v) {
            d[u]++;
            g[u].emplace_back(v, w);
            continue;
        }
        d[u]++, d[v]++;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    for (int k = 30; ~k; k--) {
        memset(a, 0, sizeof(a));
        for (int u = 1; u < n; u++) {
            a[u][u] = -d[u];
            for (auto [v, w] : g[u]) {
                if (w >> k & 1) a[u][v]--, a[u][n + 1]--;
                else a[u][v]++;
            }
        }
        a[n][n] = 1;
        gauss();
        ans += (1 << k) * a[1][n + 1];
    }
    printf("%.3LF\n", ans);

    return 0;
}