#include <bits/stdc++.h>

using namespace std;

int n, m, q;
int dis[100005][2] ;
unordered_map<int, bool> nums[100005];
vector<int> graph[100005];
bool visited[100005][2];

void dijkstra() {
    priority_queue<pair<int/*dis*/, int/*index*/>, vector<pair<int, int>>, greater<>> q; // NOLINT
    q.emplace(0, 1);
    while (!q.empty()) {
        int d = q.top().first, u = q.top().second;
        q.pop();

        if (visited[u][d % 2]) { continue; }
        else { visited[u][d % 2] = true; }

        for (auto e : graph[u]) {
            dis[e][(d + 1) % 2] = min(dis[e][(d + 1) % 2], d + 1);
            q.emplace(dis[e][(d + 1) % 2], e);
        }
    }
}

int main() {
    memset(dis, 0x7f, sizeof(dis));
    cin >> n >> m >> q;
    for (int i = 1; i <= m; i ++) {
        int u, v;
        cin >> u >> v;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }

    dis[1][0] = 0;
    dijkstra();

    for (int i = 1; i <= q; i ++) {
        int a, L;
        cin >> a >> L;
        if (L >= dis[a][L % 2]) { cout << "Yes" << endl; }
        else { cout << "No" << endl; }
    }
    return 0;
}