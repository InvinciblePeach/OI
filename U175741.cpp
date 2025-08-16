#include <bits/stdc++.h>

using namespace std;

struct edge {
    int v, w;

    edge (int v_, int w_) {
        this->v = v_;
        this->w = w_;
    }
};

int n, s, t;
int f[100005][100005][100005], g[100005][100005][100005];
vector<edge> graph[100005];

int main() {
    cin >> n >> s >> t;
    for (int i = 1; i <= n; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    for (int i = 1; i <= n; i ++) {
        for (int u = 1; u <= n; u ++) {
            for (int v = 1; v <= n; v ++) {
                f[i][u][v] = min(f[i - 1][u][v], f[i - 1][u][i] + f[i - 1][i][v])
            }
        }
    }
    return 0;
}