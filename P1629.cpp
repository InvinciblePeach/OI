#include <bits/stdc++.h>

using namespace std;

struct edge {
    int v, w;

    edge(int v_, int w_) { v = v_, w = w_; }
};

int n, m;
int ans;
int dis[100005], reverse_dis[100005];
bool visited[100005];
vector<edge> graph[100005];
vector<edge> reverse_graph[100005];

void dijkstra() {
    memset(dis, 0x7f, sizeof(dis));
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
    dis[1] = 0;
    q.emplace(0, 1);
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();

        if (visited[u]) { continue; }
        else { visited[u] = true; }

        for (auto e : graph[u]) {
            dis[e.v] = min(dis[e.v], dis[u] + e.w);
            q.emplace(dis[e.v], e.v);
        }
    }
}

void reverse_dijkstra() {
    memset(reverse_dis, 0x7f, sizeof(reverse_dis));
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
    reverse_dis[1] = 0;
    q.emplace(0, 1);
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();

        if (visited[u]) { continue; }
        else { visited[u] = true; }

        for (auto e : reverse_graph[u]) {
            reverse_dis[e.v] = min(reverse_dis[e.v], reverse_dis[u] + e.w);
            q.emplace(reverse_dis[e.v], e.v);
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        reverse_graph[v].emplace_back(u, w);
    }

    dijkstra();
    memset(visited, 0, sizeof(visited));
    reverse_dijkstra();

    for (int i = 1; i <= n; i ++) { ans += dis[i] + reverse_dis[i]; }
    cout << ans << endl;
    return 0;
}