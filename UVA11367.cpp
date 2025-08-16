#include <bits/stdc++.h>

using namespace std;

struct edge {
    int v, w;

    edge(int v_, int w_) {
        this->v = v_;
        this->w = w_;
    }
};

int n, m, T, c, s, e;
int price[1005], dis[1005][105];
bool visited[1005][105];
vector<edge> graph[1005];

bool dijkstra(int max_c, int start, int end) {
    priority_queue<tuple<int/*cost*/, int/*loc*/, int/*rest*/>, vector<tuple<int, int, int>>, greater<>> q;
    q.emplace(0, start, 0);
    dis[start][0] = 0;
    while (!q.empty()) {
        int now_cost = get<0>(q.top()), now_loc = get<1>(q.top()), now_rest = get<2>(q.top());
        q.pop();

        if (now_loc == end) { return true; }

        if (visited[now_loc][now_rest]) { continue; }
        else { visited[now_loc][now_rest] = true; }

        if (now_rest < max_c) {
            int next_rest = now_rest + 1, next_cost = now_cost + price[now_loc];
            if (next_cost < dis[now_loc][next_rest]) {
                dis[now_loc][next_rest] = next_cost;
                q.emplace(next_cost, now_loc, next_rest);
            }
        }

        for (auto & e : graph[now_loc]) { // NOLINT
            if (now_rest >= e.w) {
                int next_rest = now_rest - e.w;
                dis[e.v][next_rest] = now_cost;
                q.emplace(now_cost, e.v, next_rest);
            }
        }
    }
    return false;
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i ++) {
        cin >> price[i];
    }

    for (int i = 1; i <= m; i ++) {
        int u, v, d;
        cin >> u >> v >> d;
        graph[u].emplace_back(v, d);
        graph[v].emplace_back(u, d);
    }

    cin >> T;
    while (T --> 0) {
        memset(dis, 0x3f, sizeof(dis));
        memset(visited, false, sizeof(visited));
        cin >> c >> s >> e;
        if (dijkstra(c, s, e)) {
            cout << dis[e][0] << endl;
        } else {
            cout << "impossible" << endl;
        }
    }
    return 0;
}