#include <bits/stdc++.h>
#define int unsigned

using namespace std;

int cnt = 0, ones[(1u << 9u) + 1] = {0}, sudoku[9][9], row[9], col[9], block[3][3], Hash[37];
signed ans = -1, sum = 0;
int w[9][9] = {{6, 6, 6, 6, 6, 6, 6, 6, 6},
               {6, 7, 7, 7, 7, 7, 7, 7, 6},
               {6, 7, 8, 8, 8, 8, 8, 7, 6},
               {6, 7, 8, 9, 9, 9, 8, 7, 6},
               {6, 7, 8, 9, 10,9, 8, 7, 6},
               {6, 7, 8, 9, 9, 9, 8, 7, 6},
               {6, 7, 8, 8, 8, 8, 8, 7, 6},
               {6, 7, 7, 7, 7, 7, 7, 7, 6},
               {6, 6, 6, 6, 6, 6, 6, 6, 6}};

bool dfs(int res, signed score){
    if (res == 0){
        ans = max(ans, score);
        return true;
    }

    int x, y, min_state, min_ = INT_MAX;

    for (int i = 0; i < 9; i ++){
        for (int j = 0; j < 9; j ++){
            if (sudoku[i][j]){
                continue;
            }
            int now_state = row[i] & col[j] & block[i / 3][j / 3];
            if (ones[now_state] < min_){
                min_ = ones[now_state];
                min_state = now_state;
                x = i, y = j;
            }
        }
    }

    while (min_state){
        int num = Hash[(min_state & - min_state) % 37] + 1;
        sudoku[x][y] = num;
        row[x] ^= 1u << (num - 1);
        col[y] ^= 1u << (num - 1);
        block[x / 3][y / 3] ^= 1u << (num - 1);

        dfs(res - 1, score + num * w[x][y]); //NOLINT

        sudoku[x][y] = 0;
        row[x] ^= 1u << (num - 1);
        col[y] ^= 1u << (num - 1);
        block[x / 3][y / 3] ^= 1u << (num - 1);
        min_state -= min_state & - min_state;
    }

    return false;
}

signed main(){
    fill(row, row + 9, (1u << 9u) - 1);
    fill(col, col + 9, (1u << 9u) - 1);
    fill(block[0], block[0] + 9, (1u << 9u) - 1);

    for (int i = 0; i < 9; i ++){
        Hash[(1u << i) % 37] = i;
    }

    for (int i = 0; i < 1u << 9u; i ++){
        int j = i;
        while (j){
            ones[i] ++;
            j -= j & - j;
        }
    }

    for (int i = 0; i < 9; i ++){
        for (int j = 0; j < 9; j ++){
            cin >> sudoku[i][j];
            if (sudoku[i][j]){
                row[i] ^= 1u << (sudoku[i][j] - 1);
                col[j] ^= 1u << (sudoku[i][j] - 1);
                block[i / 3][j / 3] ^= 1u << (sudoku[i][j] - 1);
                sum += sudoku[i][j] * w[i][j];       //NOLINT
            }
            else{
                cnt ++;
            }
        }
    }

    dfs(cnt, sum);

    cout << ans << endl;

    return 0;
}