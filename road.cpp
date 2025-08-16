#include <bits/stdc++.h>
#define int long long

using namespace std;

struct edge {
    int v, w;

    edge(int v_, int w_) { v = v_, w = w_; }
};

int n, m, dis[300005];
bool visited[300005];
vector<edge> graph[300005];

void dijkstra() {
    priority_queue<tuple<int/*dis*/, int/*u*/, int/*level*/>, vector<tuple<int/*dis*/, int/*u*/, int/*level*/>>, greater<>> q;
    dis[1] = 0;
    q.emplace(0, 1, 0);
    while (!q.empty()) {
        int u = get<1>(q.top()), level = get<2>(q.top());
        q.pop();

        if (visited[u]) { continue; }
        else { visited[u] = true; }

        level ++;
        for (auto e : graph[u]) {
            dis[e.v] = min(dis[e.v], max(dis[u], e.w * level));
            q.emplace(dis[e.v], e.v, level);
        }
    }
}

signed main() {
//    freopen("road.in", "r", stdin);
//    freopen("road.out", "w", stdout);
    memset(dis, 0x7f, sizeof(dis));

    cin >> n >> m;
    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
    }

    dijkstra();
    cout << dis[n] << endl;

//    fclose(stdin);
//    fclose(stdout);
    return 0;
}