#include <bits/stdc++.h>

using namespace std;

const int dx[] = {0, 1, 1, -1, -1, 2, 2, -2, -2};
const int dy[] = {0, 2, -2, 2, -2, 1, -1, 1, -1};
const char goal[6][6] = {
        {'0', '0', '0', '0', '0', '0'},
        {'0', '1', '1', '1', '1', '1'},
        {'0', '0', '1', '1', '1', '1'},
        {'0', '0', '0', '*', '1', '1'},
        {'0', '0', '0', '0', '0', '1'},
        {'0', '0', '0', '0', '0', '0'},
};

char a[6][6];
int T;

inline int check() {
    int cnt = 0;
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            if (goal[i][j] != a[i][j]) {
                cnt ++;
            }
            if (cnt > 15) {
                return 1000;
            }
        }
    }
    return cnt;
}

bool dfs(int x, int y, int depth, int max_depth) {

    if (check() + depth - 1 > max_depth) {
        return false;
    } else if (!check()) {
        cout << depth << endl;
        return true;
    }

    for (int i = 1; i <= 8; i ++) {
        int now_x = x + dx[i], now_y = y + dy[i];
        if (now_x < 1 || now_x > 5 || now_y < 1 || now_y > 5) { continue;}
        swap(a[now_x][now_y], a[x][y]);
        if (dfs(now_x, now_y, depth + 1, max_depth)) {
            return true;
        }
        swap(a[now_x][now_y], a[x][y]);
    }

    return false;
}

int main() {
    cin >> T;
    while (T --> 0) {
        int x, y;
        for (int i = 1; i <= 5; i ++) {
            for (int j = 1; j <= 5; j ++) {
                cin >> a[i][j];
                if (a[i][j] == '*') {
                    x = i, y = j;
                }
            }
        }
        int max_depth = 1;
        bool flag = false;
        for (; max_depth <= 15; max_depth ++) {
            if (dfs(x, y, 0, max_depth)) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            cout << -1 << endl;
        }
    }
    return 0;
}