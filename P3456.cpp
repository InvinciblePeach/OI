#include <bits/stdc++.h>
#define int long long

using namespace std;

int cnt_ridge, cnt_valley;
int n, nums[1005][1005];
bool visited[1005][1005] = {false};
int dx[] = {0,-1,-1,-1, 0, 0, 1, 1, 1};
int dy[] = {0,-1, 0, 1,-1, 1,-1, 0, 1};
bool is_ridge = true, is_valley = true;

void bfs(int i, int j) {
    queue<pair<int, int>> q;
    q.emplace(make_pair(i, j));
    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        for (int k = 1; k <= 8; k ++) {
            int now_x = x + dx[k], now_y = y + dy[k];
            if (now_x <= 0 || now_x > n || now_y <= 0 || now_y > n) {
                continue;
            }

            if (nums[x][y] < nums[now_x][now_y]) {
                is_ridge = false;
            }

            if (nums[x][y] > nums[now_x][now_y]) {
                is_valley = false;
            }

            if (visited[now_x][now_y]) {
                continue;
            }
            if (nums[x][y] == nums[now_x][now_y]) {
                visited[now_x][now_y] = true;
                q.emplace(make_pair(now_x, now_y));
            }
        }
    }
}

signed main() {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            cin >> nums[i][j];
        }
    }
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            if (visited[i][j]) { continue;}
            bfs(i, j);
            if (is_ridge) {cnt_ridge ++;}
            if (is_valley) {cnt_valley ++;}
            is_ridge = true, is_valley = true;
        }
    }
    cout << cnt_ridge << ' ' << cnt_valley << endl;
    return 0;
}