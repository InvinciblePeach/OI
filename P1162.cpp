#include <bits/stdc++.h>

using namespace std;

int n, nums[55][55];
bool flag;
int dx[] = {0, 0, 0, 1, 1, 1,-1,-1,-1};
int dy[] = {0, 1,-1, 1, 0,-1, 1, 0,-1};

void bfs(int i, int j) {
    queue<pair<int, int>> q;
    q.push(make_pair(i, j));
    nums[i][j] = 2;
    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        for (int k = 1; k <= 8; k ++) {
            int now_x = x + dx[k], now_y = y + dy[k];
            if (now_x <= 0 || now_x > n || now_y <= 0 || now_y > n) {
                continue;
            }
            if (!nums[now_x][now_y]) {
                nums[now_x][now_y] = 2;
                q.push(make_pair(now_x, now_y));
            }
        }
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            cin >> nums[i][j];
        }
    }

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            if (nums[i][j] == 1) {
                bfs(i + 1, j + 1);
                flag = true;
                break;
            }
        }
        if (flag) {
            break;
        }
    }

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            cout << nums[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}