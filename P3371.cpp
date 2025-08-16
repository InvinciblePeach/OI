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
int dis[100005];
vector<edge> graph[100005];
bool visited[100005];

void dijkstra() {
    queue<int> q;
    q.emplace(s);
    visited[s] = true;
    dis[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto & e : graph[u]) {
            dis[e.v] = min(dis[e.v], dis[u] + e.w);
        }

        int min_ = INT_MAX;
        int min_index = 0;
        for (int i = 1; i <= n; i ++) {
            if (dis[i] < min_ && !visited[i]) {
                min_ = dis[i];
                min_index = i;
            }
        }

        if (min_index) {
            q.emplace(min_index);
            visited[min_index] = true;
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