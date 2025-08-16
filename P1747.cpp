#include <bits/stdc++.h>

using namespace std;

int x_1, y_1, x_2, y_2;
bool visited[105][105];
int dx[] = {0, 1, 1, 2, 2, 2, 2, -1, -1, -2, -2, -2, -2};
int dy[] = {0, -2, 2, -2, -1, 1, 2, -2, 2, -1, 1, -2, 2};

int bfs(int x, int y) {
    queue<tuple<int, int, int>> q;
    q.emplace(x, y, 0);
    while (!q.empty()) {
        int now_x = get<0>(q.front()), now_y = get<1>(q.front()), time = get<2>(q.front());
        q.pop();

        if (visited[now_x][now_y]) { continue; }
        else { visited[now_x][now_y] = true; }

        for (int i = 1; i <= 12; i ++) {
            for (int j = 1; j <= 12; j ++) {
                auto next_x = now_x + dx[i], next_y = now_y + dy[i];

                if (next_x > 100 || next_x <= 0 || next_y > 100 || next_y <= 0) { continue; }

                if (next_x == 1 && next_y == 1) { return time + 1; }

                q.emplace(next_x, next_y, time + 1);
            }
        }
    }
}

int main() {
    cin >> x_1 >> y_1 >> x_2 >> y_2;
    cout << bfs(x_1, y_1) << endl;

    for (auto & i : visited)
    for (auto & j : i) { j = false; }

    cout << bfs(x_2, y_2) << endl;

    return 0;
}