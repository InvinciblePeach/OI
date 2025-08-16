#include <bits/stdc++.h>

using namespace std;

struct edge {
    int v, w, level;

    inline edge(int v_, int w_, int level_) {
        this->v = v_;
        this->w = w_;
        this->level = level_;
    }
};

int n, m, k;
int dis[55][5005];
bool visited[55][5005];
vector<edge> graph[55][5005];

void dijkstra() {
    priority_queue<tuple<int/*dis*/, int/*index*/, int/*level*/>, vector<tuple<int/*dis*/, int/*index*/, int/*level*/>>, greater<>> q; // NOLINT
    q.emplace(0, 1, 1);
    dis[1][1] = 0;
    while (!q.empty()) {
        auto u = get<1>(q.top()), level = get<2>(q.top());
        q.pop();

        if (visited[level][u]) { continue; }
        else { visited[level][u] = true; }

        for (auto & e : graph[level][u]) {
            dis[e.level][e.v] = min(dis[e.level][e.v], dis[level][u] + e.w);
            q.emplace(dis[e.level][e.v], e.v, e.level);
        }
    }
}

int main() {
    cin >> n >> m >> k;

    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        for (int j = 1; j <= k + 1; j ++) {
            graph[j][u].emplace_back(v, w, j);
            graph[j][v].emplace_back(u, w, j);
            graph[j][u].emplace_back(v, w / 2, j + 1);
            graph[j][v].emplace_back(u, w / 2, j + 1);
        }
    }

    for (int i = 1; i <= k + 1; i ++) {
        for (int j = 1; j <= n; j ++) {
            dis[i][j] = INT_MAX;
        }
    }

    dijkstra();

    int ans = INT_MAX;
    for (int i = 1; i <= k + 1; i ++) {
        ans = min(dis[i][n], ans);
    }

    cout << ans << endl;

    return 0;
}