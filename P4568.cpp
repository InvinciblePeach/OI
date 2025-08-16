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

int n, m, k, s, t;
int dis[15][10005];
bool visited[15][10005];
vector<edge> graph[15][10005];

void dijkstra() {
    priority_queue<tuple<int/*dis*/, int/*index*/, int/*level*/>, vector<tuple<int, int, int>>, greater<>> q;
    q.emplace(0, s, 0);
    dis[0][s] = 0;
    while (!q.empty()) {
        auto u = get<1>(q.top()), level = get<2>(q.top());
        q.pop();

        if (visited[level][u]) { continue; }
        else { visited[level][u] = true; }

        for (auto e : graph[level][u]) {
            dis[e.level][e.v] = min(dis[e.level][e.v], dis[level][u] + e.w);
            q.emplace(dis[e.level][e.v], e.v, e.level);
        }
    }
}

int main() {
    cin >> n >> m >> k >> s >> t;

    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        for (int j = 0; j <= k; j ++) {
            graph[j][u].emplace_back(v, w, j);
            graph[j][v].emplace_back(u, w, j);
            graph[j][u].emplace_back(v, 0, j + 1);
            graph[j][v].emplace_back(u, 0, j + 1);
        }
    }

    for (int i = 0; i <= k; i ++) {
        for (int j = 0; j < n; j ++) {
            if (j == s) { dis[i][j] = 0; }
            dis[i][j] = INT_MAX;
        }
    }

    dijkstra();

    int ans = INT_MAX;
    for (int i = 0; i <= k; i ++) {
        ans = min(dis[i][t], ans);
    }

    cout << ans << endl;

    return 0;
}