#include <bits/stdc++.h>

using namespace std;

int n, x_1, y_1, x_2, y_2;
char graph[1005][1005];
bool visited[1005][1005];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int bfs(int x, int y) {
    queue<tuple<int, int, int>> q;
    q.emplace(x, y, 0);
    while (!q.empty()) {
        int now_x = get<0>(q.front()), now_y = get<1>(q.front()), time = get<2>(q.front());
        q.pop();

        if (visited[now_x][now_y]) { continue; }
        else { visited[now_x][now_y] = true; }

        for (int i = 0; i < 4; i ++) {
            int next_x = now_x + dx[i], next_y = now_y + dy[i];

            if (next_x > n || next_x <= 0 || next_y > n || next_y <= 0 || graph[next_x][next_y] == '1') { continue; }
            if (next_x == x_2 && next_y == y_2) { return time + 1; }

            q.emplace(next_x, next_y, time + 1);
        }
    }
}

int main() {
    cin >> n;

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            cin >> graph[i][j];
        }
    }

    cin >> x_1 >> y_1 >> x_2 >> y_2;

    cout << bfs(x_1, y_1) << endl;

    return 0;
}