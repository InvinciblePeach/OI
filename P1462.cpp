#include <bits/stdc++.h>

using namespace std;

struct edge {
    int v, w;

    edge(int v_, int w_) { v = v_, w = w_; }
};

int n, m, b, num[10005], dis[10005];
bool visited[10005];
vector<edge> graph[10005];

void dijkstra() {
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> q;
    dis[1] = 0;
    q.emplace(dis[1], 1, b);

    while (!q.empty()) {
        int u = get<1>(q.top()), now_b = get<2>(q.top());
        q.pop();

        if (now_b <= 0 || visited[u]) { continue; }
        else { visited[u] = true; }

        for (auto e : graph[u]) {
            if (now_b - e.v < 0) { continue; }
            dis[e.v] = min(dis[e.v], dis[u] + num[u]);
            q.emplace(dis[e.v], e.v, now_b - e.v);
        }
    }
}

int main() {
    cin >> n >> m >> b;
    memset(dis, 0x7f, sizeof(dis));

    for (int i = 1; i <= n; i ++) { cin >> num[i]; }
    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
    }

    dijkstra();

    cout << dis[n] << endl;

    return 0;
}