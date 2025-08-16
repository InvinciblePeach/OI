#include <bits/stdc++.h>

using namespace std;

const int mod = 100003;
int n, m, dis[1000005], num[1000005];
bool visited[1000005];
vector<int> graph[1000005];

void bfs() {
    queue<int> q;
    q.emplace(1);
    dis[1] = 0;
    num[1] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (visited[u]) {
            continue;
        } else {
            visited[u] = true;
        }

        for (auto v : graph[u]) {
            if (dis[u] + 1 <= dis[v]) {
                dis[v] = dis[u] + 1;
                num[v] += num[u];
                num[v] %= mod;
                q.emplace(v);
            }
        }
    }
}

int main() {
    memset(dis, 0x7f, sizeof(dis));
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }

    bfs();

    for (int i = 1; i <= n; i++) {
        cout << num[i] << endl;
    }
    return 0;
}