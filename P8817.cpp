#include <bits/stdc++.h>
#define int long long

using namespace std;

int n, m, k, num[2505], visited[2505], ans = INT_MIN, dis[2505];
bool tmp_graph[2505][2505];
bool graph[2505][2505];

inline bool check(vector<int> v, int a) {
    for (auto i : v) {
        if (i == a) {
            return true;
        }
    }
    return false;
}

void bfs(int i) {
    queue<pair<int/*index*/, int/*dis*/>> q;
    q.emplace(i, -1);
    while (!q.empty()) {
        int u = q.front().first, now_dis = q.front().second;
        q.pop();

        if (now_dis >= k) { break; }

        for (int v = 1; v <= n; v ++) {
            if (tmp_graph[u][v]) {
                q.emplace(v, now_dis + 1);
                graph[i][v] = true;
                graph[v][i] = true;
            }
        }
    }
    graph[i][i] = false;
}

void dijskra() {
  priority_queue<pair<int, int>, vector<int, int>, greater<>> pq;
  dis[1] = -1;
  pq.emplace(dis[1], 1);
  while (!pq.empty()) {
    int u = pq.top().second;

    if (visited[u]) { continue; }
    else { visited[u] = true; }

    for (auto v : graph[u]) {
      dis[v] = min(dis[v], dis[u] + 1);
      pq.emplace(dis[v], v);
    }
  }
}

void A_star() {
	priority_queue<int> pq;
}

signed main() {
    freopen("holiday.in", "r", stdin);
    freopen("holiday.out", "w", stdout);
    cin >> n >> m >> k;
    for (int i = 2; i <= n; i ++) { cin >> num[i]; }
    for (int i = 1; i <= m; i ++) {
        int x, y;
        cin >> x >> y;
        tmp_graph[x][y] = true;
        tmp_graph[y][x] = true;
        graph[x][y] = true;
        graph[x][y] = true;
    }

    for (int i = 1; i <= n; i ++) { bfs(i); }
    memset(dis, 0x3f, sizeof(dis));
    dijskra();
    A_star();

    cout << ans << endl;
    fclose(stdin);
    fclose(stdout);
    return 0;
}
