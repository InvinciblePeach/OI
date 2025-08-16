#include <bits/stdc++.h>

using namespace std;

const int id[10][10]=
        { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 1, 1, 1, 2, 2, 2, 3, 3, 3},
          {0, 1, 1, 1, 2, 2, 2, 3, 3, 3},
          {0, 1, 1, 1, 2, 2, 2, 3, 3, 3},
          {0, 4, 4, 4, 5, 5, 5, 6, 6, 6},
          {0, 4, 4, 4, 5, 5, 5, 6, 6, 6},
          {0, 4, 4, 4, 5, 5, 5, 6, 6, 6},
          {0, 7, 7, 7, 8, 8, 8, 9, 9, 9},
          {0, 7, 7, 7, 8, 8, 8, 9, 9, 9},
          {0, 7, 7, 7, 8, 8, 8, 9, 9, 9}};

bool row[10], col[10], block[10];

inline int check() {
    int cnt_row = 0, cnt_col = 0, cnt_block = 0;
    for (int i = 1; i <= 9; i ++) {
        if (!row[i]) {
            cnt_row ++;
        }
        if (!col[i]) {
            cnt_col ++;
        }
        if (!block[i]) {
            cnt_block ++;
        }
    }
    return max({cnt_row, cnt_col, cnt_block});
}

bool dfs(int x, int depth, int max_depth) {
    if (check() + depth - 1 > max_depth) {
        return false;
    } else if (!check()) {
        cout << depth << endl;
        return true;
    }

    for (int i = x; i <= 9; i ++) {
        for (int j = 1; j <= 9; j ++) {

            if (row[i] && col[j] && block[id[i][j]]) {
                continue;
            }

            row[i] = !row[i];
            col[j] = !col[j];
            block[id[i][j]] = !block[id[i][j]];

            if (dfs(i, depth + 1, max_depth)) {
                return true;
            }

            row[i] = !row[i];
            col[j] = !col[j];
            block[id[i][j]] = !block[id[i][j]];
        }
    }

    return false;
}

int main() {
    fill(row, row + 10, true);
    fill(col, col + 10, true);
    fill(block, block + 10, true);

    for (int i = 1; i <= 9; i ++) {
        for (int j = 1; j <= 9; j ++) {
            char a;
            cin >> a;
            if (a - '0') {
                row[i] = !row[i];
                col[j] = !col[j];
                block[id[i][j]] = !block[id[i][j]];
            }
        }
    }

    for (int max_depth = 1; max_depth <= 9; max_depth ++) {
        if (dfs(1, 0, max_depth)) {
            break;
        }
    }

    return 0;
}