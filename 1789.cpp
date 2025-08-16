#include <bits/stdc++.h>
#define x first
#define y second

using namespace std;

int n, m;
char graph[805][805];
int visited[805][805];
pair<int, int> boy, girl, ghost[2]; // NOLINT
int cnt;

int dx[] = {0, 0, 0, 1, -1, 0, 0, 2, -2, 0, 0, 3, -3};
int dy[] = {0, 1, -1, 0, 0, 2, -2, 0, 0, 3, -3, 0, 0};

bool ghosted(int a, int b, int time) {
    for (auto i : ghost) {
        if (abs(i.x - a) + abs(i.y - b) <= 2 * time) {
            return true;
        }
    }
    return false;
}

int bfs() {
    queue<pair<pair<int, int>, int>> boy_q;
    queue<pair<pair<int, int>, int>> girl_q;

    boy_q.emplace(boy, 1);
    girl_q.emplace(girl, 1);

    visited[boy.x][boy.y] = 1;
    visited[girl.x][girl.y] = 2;

    while (!boy_q.empty()) {
        int boy_x = boy_q.front().first.x, boy_y = boy_q.front().first.y;
        int girl_x = girl_q.front().first.x, girl_y = girl_q.front().first.y;
        int time = boy_q.front().second;
        boy_q.pop(); girl_q.pop();

        if (ghosted(boy_x, boy_y, time)) { continue; }
        if (ghosted(girl_x, girl_y, time)) { continue; }

        if (boy_x == girl_x && boy_y == girl_y) { return time; }


        for (int i = 1; i <= 12; i ++) {
            for (int j = 1; j <= 4; j ++) {
                int now_boy_x = boy_x + dx[i], now_boy_y = boy_y + dy[i];
                int now_girl_x = girl_x + dx[j], now_girl_y = girl_y + dy[j];

                if (now_boy_x <= 0 || now_boy_y > n) { continue; }
                if (now_girl_x <= 0 || now_girl_y > n) { continue; }

                if (visited[now_boy_x][now_boy_y] == 1) { continue; }
                if (visited[now_girl_x][now_girl_y] == 2) { continue; }

                if (graph[now_boy_x][now_boy_y] == 'X') { continue; }
                if (graph[now_girl_x][now_girl_y] == 'X') { continue; }

                boy_q.emplace(make_pair(now_boy_x, now_boy_y), time + 1);
                girl_q.emplace(make_pair(now_girl_x, now_girl_y), time + 1);
            }
        }
    }

    return -1;
}

int main() {
    cin >> n >> m;

    for (int i = 1; i < n; i ++) {
        for (int j = 1; j < m; j ++) {
            cin >> graph[i][j];
            if (graph[i][j] == 'Z') { ghost[cnt++] = make_pair(i, j); }
            else if (graph[i][j] == 'M') { boy = make_pair(i, j); }
            else if (graph[i][j] == 'G') { girl = make_pair(i, j); }
        }
    }

    cout << bfs() << endl;

    return 0;
}