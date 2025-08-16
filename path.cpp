#include <bits/stdc++.h>
#define int long long

using namespace std;

struct edge {
    int v, w;

    edge(int v_, int w_) { v = v_, w = w_; }
};

int T, P, k, Q;
int dis[100005];
bool visited[100005];
vector<edge> graph[100005];

void dijkstra(int s) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q; // NOLINT
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

signed main() {
//    freopen("path.in", "r", stdin);
//    freopen("path.out", "w", stdout);
    cin >> T;
    while (T --> 0) {
        memset(graph, 0, sizeof(graph));
        cin >> P >> k >> Q;
        for (int x = 0; x < P; x ++) {
            for (int i = 0; i < k; i ++) {
                graph[x].emplace_back((k * x + i) % P, i);
            }
        }
        for (int i = 1; i <= Q; i ++) {
            memset(dis, 0x7f, sizeof(dis));
            memset(visited, 0, sizeof(visited));
            int u, v;
            cin >> u >> v;
            dijkstra(u);
            cout << ((dis[v] == 0x7f7f7f7f7f7f7f7f) ? -1 : dis[v]) << endl;
        }
    }
//    fclose(stdin);
//    fclose(stdout);
    return 0;
}