#include <bits/stdc++.h>
#define int unsigned int

using namespace std;

char sudoku[16][16], now_sudoku[16 * 16 + 1][16][16], now_sudoku2[16 * 16 + 1][16][16];
int state[16][16], now_state[16 * 16 + 1][16][16], now_state2[16 * 16 + 1][16][16];
int ones[(1u << 16u) + 1];
int K;

void show(){
    for (auto & i : sudoku){
        for (auto & j : i){
            cout << j;
        }
        cout << endl;
    }
}

void state_update(int x, int y, int num){
    sudoku[x][y] = num + 'A';           // NOLINT

    for (int i = 0; i < 16; i++){
        state[x][i] &= ~(1u << num);
        state[i][y] &= ~(1u << num);
    }

    int block_x = x / 4 * 4, block_y = y / 4 * 4;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            state[block_x + i][block_y + j] &= ~(1u << num);
        }
    }

    state[x][y] = 1u << num;
}

bool dfs(int cnt){
    if (!cnt){
        return true;
    }


    // prune 1:

    int now_cnt = cnt;
    memcpy(now_state[now_cnt], state, sizeof(state));
    memcpy(now_sudoku[now_cnt], sudoku, sizeof(sudoku));
    for (int i = 0; i < 16; i ++){
        for (int j = 0; j < 16; j ++){
            if (sudoku[i][j] != '-'){
                continue;
            }
            if (state[i][j] == 0){
                memcpy(state, now_state[now_cnt], sizeof(state));
                memcpy(sudoku, now_sudoku[now_cnt], sizeof(sudoku));
                return false;
            }

            if (ones[state[i][j]] == 1){
                state_update(i, j, signed(log2(state[i][j])));
                cnt --;
            }
        }
    }

    // prune 2:

    for (int i = 0; i < 16; i++){
        int alpha_set = 0, locked_set = (1u << 16u) - 1, used_alpha = 0;
        for (int j = 0; j < 16; j++){
            locked_set &= ~(alpha_set & state[i][j]);
            alpha_set |= state[i][j];

            if (sudoku[i][j] != '-'){
                used_alpha |= 1u << (sudoku[i][j] - 'A'); // NOLINT
            }
        }

        if (alpha_set != (1u << 16u) - 1){
            memcpy(state, now_state[now_cnt], sizeof(state));
            memcpy(sudoku, now_sudoku[now_cnt], sizeof(sudoku));
            return false;
        }

        while (locked_set){
            int tmp = locked_set & -locked_set;
            if(!(used_alpha & tmp)){
                for (int j = 0; j < 16; j ++){
                    if (tmp & state[i][j]){
                        state_update(i, j, signed(log2(tmp)));
                        cnt --;
                        break;
                    }
                }
            }
            locked_set -= tmp;
        }
    }

    // prune 3:

    for (int j = 0; j < 16; j++){
        int alpha_set = 0, locked_set = (1u << 16u) - 1, used_alpha = 0;
        for (int i = 0; i < 16; i++){
            locked_set &= ~(alpha_set & state[i][j]);
            alpha_set |= state[i][j];

            if (sudoku[i][j] != '-'){
                used_alpha |= state[i][j]; // NOLINT
            }
        }

        if (alpha_set != (1u << 16u) - 1){
            memcpy(state, now_state[now_cnt], sizeof(state));
            memcpy(sudoku, now_sudoku[now_cnt], sizeof(sudoku));
            return false;
        }

        while (locked_set){
            int tmp = locked_set & -locked_set;
            if(!(used_alpha & tmp)){
                for (int i = 0; i < 16; i ++){
                    if (tmp & state[i][j]){
                        state_update(i, j, signed(log2(tmp)));
                        cnt --;
                        break;
                    }
                }
            }
            locked_set -= tmp;
        }
    }

    // prune 4:

    for(int i = 0; i < 16; i++){
        int alpha_set = 0, locked_set = (1u << 16u) - 1, used_alpha = 0;
        for (int j = 0; j < 16; j++){
            int block_x = i / 4 * 4, block_y = i % 4 * 4;
            int dx = j / 4, dy = j % 4;
            locked_set &= ~(alpha_set & state[block_x + dx][block_y + dy]);
            alpha_set |= state[block_x + dx][block_y + dy];

            if (sudoku[block_x + dx][block_y + dy] != '-'){
                used_alpha |= state[block_x + dx][block_y + dy]; // NOLINT
            }
        }

        if (alpha_set != (1u << 16u) - 1){
            memcpy(state, now_state[now_cnt], sizeof(state));
            memcpy(sudoku, now_sudoku[now_cnt], sizeof(sudoku));
            return false;
        }

        while (locked_set){
            int tmp = locked_set & -locked_set;
            if(!(used_alpha & tmp)){
                for (int j = 0; j < 16; j ++){
                    int block_x = i / 4 * 4, block_y = i % 4 * 4;
                    int dx = j / 4, dy = j % 4;
                    if (tmp & state[block_x + dx][block_y + dy]){
                        state_update(block_x + dx, block_y + dy, signed(log2(tmp)));
                        cnt --;
                        break;
                    }
                }
            }
            locked_set -= tmp;
        }
    }

    // prune 5:

    if (!cnt){
        return true;
    }

    int x, y, min_ = 100, min_state;
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (sudoku[i][j] != '-') {
                continue;
            }
            if (ones[state[i][j]] < min_) {
                min_ = ones[state[i][j]];
                x = i, y = j;
                min_state = state[i][j];
            }
        }
    }

    memcpy(now_state2[now_cnt], state, sizeof(state));
    memcpy(now_sudoku2[now_cnt], sudoku, sizeof(sudoku));

    while (min_state){
        int num = signed(log2(min_state & -min_state));
        state_update(x, y, num);

        if (dfs(cnt - 1)){
            return true;
        }

        memcpy(state, now_state2[now_cnt], sizeof(state));
        memcpy(sudoku, now_sudoku2[now_cnt], sizeof(sudoku));

        min_state -= min_state & -min_state;
    }

    memcpy(state, now_state2[now_cnt], sizeof(state));
    memcpy(sudoku, now_sudoku2[now_cnt], sizeof(sudoku));

    return false;
}

signed main(){
    for (int i = 0; i < 1u << 16u; i++) {
        int tmp = i;
        while (tmp) {
            ones[i] ++;
            tmp -= tmp & -tmp;
        }
    }

    cin >> K;
    for (int k = 1; k <= K; k++){

        fill(state[0], state[0] + 256, (1u << 16u) - 1);

        int cnt = 0;

        for (auto & i : sudoku) {
            cin >> i;
        }

        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                if (sudoku[i][j] == '-') {
                    cnt++;
                }
                else {
                    state_update(i, j, sudoku[i][j] - 'A');
                }
            }
        }

        dfs(cnt);

        show();
    }

    return 0;
}

