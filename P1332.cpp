#include <bits/stdc++.h>

using namespace std;

int n, m, a, b;
int graph[505][505];
bool visited[505][505];
vector<pair<int, int>> sources;

int dx[] = {0, 1,-1, 0, 0};
int dy[] = {0, 0, 0, 1,-1};

void bfs() {
    queue<pair<int, int>> q;
    for (auto i : sources) {
        q.emplace(i);
        visited[i.first][i.second] = true;
    }

    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        for (int i = 1; i <= 4; i ++) {
            int now_x = x + dx[i], now_y = y + dy[i];

            if (now_x <= 0 || now_x > n || now_y <= 0 || now_y > m) { continue;}
            if (visited[now_x][now_y]) { continue;}

            graph[now_x][now_y] = graph[x][y] + 1;
            q.emplace(now_x, now_y);
            visited[now_x][now_y] = true;
        }
    }
}

int main() {
    cin >> n >> m >> a >> b;

    for (int i = 1; i <= a; i ++) {
        int x, y;
        cin >> x >> y;
        sources.emplace_back(x, y);
    }

    bfs();

    for (int i = 1; i <= b; i ++) {
        int x, y;
        cin >> x >> y;
        cout << graph[x][y] << endl;
    }

    return 0;
}