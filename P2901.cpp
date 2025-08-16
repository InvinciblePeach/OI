#include <bits/stdc++.h>

using namespace std;

struct edge {
    int v, w;

    edge(int v_, int w_) {
        this->v = v_;
        this->w = w_;
    }
};

int n, m, k, s, t;
int dis[1005];
bool visited[1005];
vector<edge> real_graph[1005];
vector<edge> reverse_graph[1005];

void dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
    q.emplace(0, t);
    dis[t] = 0;
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();

        if (visited[u]) { continue; }
        else { visited[u] = true; }

        for (auto e : reverse_graph[u]) {
            if (dis[e.v] > dis[u] + e.w) {
                dis[e.v] = dis[u] + e.w;
                q.emplace(dis[e.v], e.v);
            }
        }
    }
}

void bfs() {
    priority_queue<tuple<int/*eval_dis*/, int/*real_dis*/, int/*now_index*/>, vector<tuple<int, int, int>>, greater<>> q;
    q.emplace(dis[s], 0, s);
    int cnt = 0;
    while (!q.empty()) {
        int real = get<1>(q.top()), u = get<2>(q.top());
        q.pop();

        if (u == t) {
            cnt ++;
            if (cnt > k) { return; }
            cout << real << endl;
            continue;
        }

        for (auto e : real_graph[u]) {
            int next_real = real + e.w;
            q.emplace(next_real + dis[e.v], next_real, e.v);
        }
    }
    for (int i = cnt; i < k; i ++) { cout << -1 << endl; }
}

int main() {
    memset(dis, 0x3f, sizeof(dis));

    cin >> n >> m >> k;
    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        real_graph[u].emplace_back(v, w);
        reverse_graph[v].emplace_back(u, w);
    }
    s = n, t = 1;

    dijkstra();

    bfs();
}