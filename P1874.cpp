#include <bits/stdc++.h>
#define ull unsigned long long

using namespace std;

long long n;

bool sudoku[9][9];    //NOLINT
int ones[37], row[9], col[9], block[9][9], Hash[37];
ull nums[9];

bool dfs(int res){
    if (res == 0){
        return true;
    }
    int x, y, min_state, min_ = INT_MAX;
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (sudoku[i][j]){
                continue;
            }
            int now_state = row[i] & col[j] & block[i / 3][j / 3];
            if (ones[now_state] < min_){
                min_ = ones[now_state];
                min_state = now_state;
                x = i; y = j;
            }
        }
    }

    while(min_state){
        unsigned int num = Hash[(min_state & -min_state) % 37] + 1;
        sudoku[x][y] = num;
        row[x] ^= 1ull << (num - 1);
        col[x] ^= 1ull << (num - 1);
        block[x / 3][y / 3] ^= 1ull << (num - 1);

        if (dfs(res - 1)){
            return true;
        }

        sudoku[x][y] = false;
        row[x] ^= 1ull << (num - 1);
        col[x] ^= 1ull << (num - 1);
        block[x / 3][y / 3] ^= 1ull << (num - 1);
        min_state -= min_state & -min_state;
    }
    return false;
}

int main(){
    fill(row, row + 9, (1 << 9) - 1);
    fill(col, col + 9, (1 << 9) - 1);
    fill(block[0], block[0] + 9, (1 << 9) - 1);

    for (int i = 0; i < 9; i++){
        Hash[(1 << i) % 37] = i;
    }

    for (int i = 0; i < 1 << 9; i++){
        int j = i;
        while (j){
            ones[i] += 1;
            j -= j & -j;
        }
    }

    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            cin << sudoku[i][j];
            if (sudoku[i][j]){
                row[i] ^= 1 << (sudoku[i][j] - 1);
                col[j] ^= 1 << (sudoku[i][j] - 1);
                row[i] ^= 1 << (sudoku[i][j] - 1);
            }
        }
    }

    return 0;
}