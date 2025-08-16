#include <bits/stdc++.h>

using namespace std;

bool visited[405][405];
int graph[405][405];
int n, m, x, y;

const int dx[] = {0, 1, 1, -1, -1, 2, 2, -2, -2};
const int dy[] = {0, 2, -2, 2, -2, 1, -1, 1, -1};

void bfs() {
    queue<pair<int, int>> q;
    q.emplace(make_pair(x, y));
    visited[x][y] = true;
    graph[x][y] = 0;
    while (!q.empty()) {
        int x_ = q.front().first, y_ = q.front().second;
        q.pop();
        for (int i = 1; i <= 8; i ++) {
            int now_x = x_ + dx[i], now_y = y_ + dy[i];

            if (now_x <= 0 || now_x > n || now_y <= 0 || now_y > m) { continue; }
            if (visited[now_x][now_y]) { continue; }

            graph[now_x][now_y] = graph[x_][y_] + 1;
            visited[now_x][now_y] = true;
            q.emplace(make_pair(now_x, now_y));
        }
    }
}

int main() {
    memset(graph, -1, sizeof(graph));
    cin >> n >> m >> x >> y;

    bfs();

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            cout << graph[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}
