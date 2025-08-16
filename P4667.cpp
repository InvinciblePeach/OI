#include <bits/stdc++.h>

using namespace std;

const int dx_1[] = {0, -1, -1,  1,  1};
const int dy_1[] = {0, -1,  1, -1,  1};
const int dx_2[] = {0, -1, -1,  0,  0};
const int dy_2[] = {0, -1,  0, -1,  0};
const char c[] = {' ', '\\', '/', '/', '\\'};

int n, m;
char graph[505][505];
int dis[505][505];
bool visited[505][505];

bool bfs() {
    memset(dis, 0x3f, sizeof(dis));
    deque<pair<int, int>> q;
    q.emplace_back(0, 0);
    dis[0][0] = 0;

    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop_front();

        if (visited[x][y]) { continue; }
        else { visited[x][y] = true; }

        if (x == n && y == m) {
            return true;
        }

        for (int i = 1; i <= 4; i ++) {
            int now_x = x + dx_1[i], now_y = y + dy_1[i];
            int block_x = x + dx_2[i], block_y = y + dy_2[i];

            if (now_x < 0 || now_x > n || now_y < 0 || now_y > m) { continue; }
            if (block_x < 0 || block_x >= n || block_y < 0 || block_y >= m) { continue; }

            int now_dis = dis[x][y] + (graph[block_x][block_y] != c[i]);

            if (now_dis < dis[now_x][now_y]) {
                if (graph[block_x][block_y] == c[i]) { q.emplace_front(now_x, now_y); }
                else { q.emplace_back(now_x, now_y); }
                dis[now_x][now_y] = now_dis;
            }
        }
    }
    return false;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            cin >> graph[i][j];
        }
    }

    if (bfs()) { cout << dis[n][m] << endl; }
    else { cout << "NO SOLUTION" << endl; }
    return 0;
}