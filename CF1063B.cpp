#include <bits/stdc++.h>

using namespace std;

int cnt;
int n, m, r, c, x, y;
char graph[2005][2005];
bool visited[2005][2005];
int dis[2005][2005];
int dx[] = {0, 1, -1, 0, 0};
int dy[] = {0, 0, 0, 1, -1};

void bfs() {
    deque<pair<int, int>> q;
    q.emplace_back(r, c);
    dis[r][c] = 0;
    while (!q.empty()) {
        int now_i = q.front().first, now_j = q.front().second, now_x = dis[now_i][now_j];
        q.pop_front();

        visited[now_i][now_j] = false;

        for (int i = 1; i <= 4; i ++) {
            int next_i = now_i + dx[i], next_j = now_j + dy[i], next_x = now_x + (i == 4);

            if (next_i <= 0 || next_i > n || next_j <= 0 || next_j > m || graph[next_i][next_j] == '*') { continue; }
            if (visited[next_i][next_j]) { continue; }
            if (next_x > x || next_j - (c - next_x) > y) { continue; }
            if (next_x >= dis[next_i][next_j]) { continue; }
            dis[next_i][next_j] = next_x;

            if (i == 4) { q.emplace_back(next_i, next_j); }
            else { q.emplace_front(next_i, next_j); }
            visited[next_i][next_j] = true;
        }
    }
}

int main() {
    cin >> n >> m >> r >> c >> x >> y;

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            cin >> graph[i][j];
        }
    }

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            dis[i][j] = INT_MAX;
        }
    }

    bfs();

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            if (dis[i][j] != INT_MAX) { end_ ++; }
        }
    }

    cout << end_ << endl;

    return 0;
}