#include <bits/stdc++.h>

using namespace std;

unsigned int cnt = 0, ones[1000] = {0}, sudoku[9][9], row[9], col[9], block[3][3], Hash[38];

bool dfs(unsigned int res){
    if (res == 0){
        return true;
    }

    unsigned x, y, min_state, min_ = INT_MAX;

    for (int i = 0; i < 9; i ++){
        for (int j = 0; j < 9; j ++){
            if (sudoku[i][j]){
                continue;
            }
            unsigned int now_state = row[i] & col[j] & block[i / 3][j / 3];
            if (ones[now_state] < min_){
                min_ = ones[now_state];
                min_state = now_state;
                x = i, y = j;
            }
        }
    }

    while (min_state){
        unsigned int num = Hash[(min_state & - min_state) % 37] + 1;
        sudoku[x][y] = num;
        row[x] ^= 1u << (num - 1);
        col[y] ^= 1u << (num - 1);
        block[x / 3][y / 3] ^= 1u << (num - 1);

        if (dfs(res - 1)){
            return true;
        }
        else{
            sudoku[x][y] = 0;
            row[x] ^= 1u << (num - 1);
            col[y] ^= 1u << (num - 1);
            block[x / 3][y / 3] ^= 1u << (num - 1);
            min_state -= min_state & - min_state;
        }
    }

    return false;
}

int main(){
    fill(row, row + 9, (1u << 9u) - 1);
    fill(col, col + 9, (1u << 9u) - 1);
    fill(block[0], block[0] + 9, (1u << 9u) - 1);

    for (unsigned int i = 0; i < 9; i ++){
        Hash[(1u << i) % 37] = i;
    }

    for (unsigned int i = 0; i < 1u << 9u; i ++){
        unsigned int j = i;
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
            }
            else{
                cnt ++;
            }
        }
    }

    dfs(cnt);

    for (auto & i : sudoku){
        for (auto j : i){
            cout << j << ' ';
        }
        cout << endl;
    }

    return 0;
}