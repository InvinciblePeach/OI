#include <bits/stdc++.h>

using namespace std;

struct edge {
    int v, w;

    inline edge(const int & v_, const int & w_) {
        this->v = v_;
        this->w = w_;
    }
};

int n, m, s;
int dis[1000005];
vector<edge> graph[1000005];
bool visited[1000005];

void dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
    q.emplace(0, s);
    dis[s] = 0;
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();

        if (visited[u]) { continue; }
        else { visited[u] = true; }

        for (auto & e : graph[u]) {
            dis[e.v] = min(dis[e.v], dis[u] + e.w);
            q.emplace(dis[e.v], e.v);
        }
    }
}

int main() {

    cin >> n >> m >> s;

    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
    }

    for (int i = 1; i <= n; i ++) {
        dis[i] = INT_MAX;
    }

    dijkstra();

    for (int i = 1; i <= n; i ++) {
        cout << dis[i] << ' ';
    }

    cout << endl;

    return 0;
}