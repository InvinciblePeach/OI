#include <bits/stdc++.h>

using namespace std;

int t;
int x, y;
int dis[100005];
bool visited[100005];

void bfs() {
    queue<int> q;
    q.emplace(x);
    while (!q.empty()) {
        int now_x = q.front();
        q.pop();

        if (now_x - 1 > 0) {
            dis[now_x - 1] = min(dis[now_x] + 1, dis[now_x - 1]);
            if (!visited[now_x - 1]) {
                visited[now_x - 1] = true;
                q.emplace(now_x - 1);
            }
        }

        if (now_x + 1 <= 100001) {
            dis[now_x + 1] = min(dis[now_x] + 1, dis[now_x + 1]);
            if (!visited[now_x + 1]) {
                visited[now_x + 1] = true;
                q.emplace(now_x + 1);
            }
        }

        if (now_x * 2 <= 100001) {
            dis[now_x * 2] = min(dis[now_x] + 1, dis[now_x * 2]);
            if (!visited[now_x * 2]) {
                visited[now_x * 2] = true;
                q.emplace(now_x * 2);
            }
        }
    }
}

int main() {
    cin >> t;
    while (t --> 0) {
        memset(visited, false, sizeof(visited));
        memset(dis, 0x3f, sizeof(dis));
        cin >> x >> y;
        dis[x] = 0;
        bfs();
        cout << dis[y] << endl;
    }
    return 0;
}