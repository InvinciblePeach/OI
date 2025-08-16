#include <bits/stdc++.h>
#define int long long

using namespace std;

struct edge {
    int v, w;

    edge(int v_, int w_) { v = v_, w = w_; }

    bool operator< (const edge & other) const { return w < other.w; }
};

int n, m, k, dis[100005];
bool visited[100005];
priority_queue<int, vector<int>, greater<>> ans; // NOLINT
vector<edge> graph[100005];

void dijkstra(int s) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
    q.emplace(0, s);
    dis[s] = 0;
    int cnt = 0;
    while (cnt <= k && !q.empty()) {
        int u = q.top().second;
        q.pop();

        if (visited[u]) { continue; }
        else { visited[u] = true, cnt ++, ans.emplace(dis[u]); }

        for (int i = 0; i < min(k, (int)(graph[u].size())); i ++)  {
            auto e = graph[u][i];
            dis[e.v] = min(dis[e.v], dis[u] + e.w);
            q.emplace(dis[e.v], e.v);
        }
    }
}


signed main() {
    freopen("city4.in", "r", stdin);
    freopen("city.ans", "w", stdout);

    cin >> n >> m >> k;
    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    for (int i = 1; i <= n; i ++) { sort(graph[i].begin(), graph[i].end()); }

    for (int i = 1; i <= n; i ++) {
        memset(dis, 0x7f, sizeof(dis));
        memset(visited, false, sizeof(visited));
        dijkstra(i);
        ans.pop();
        for (int j = 1; j <= k; j ++) {
            cout << ans.top() << ' ';
            ans.pop();
        }
        cout << endl;
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}