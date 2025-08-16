#include <bits/stdc++.h>

using namespace std;

long long ans = 0;
unsigned ones[1000] = {0}, row[9], col[9], block[3][3], Hash[38];
vector<pair<int, int>> tags[256];
char nums[30] = {0};
char sudoku[9][9], now_sudoku[9][9];

void dfs(unsigned res);

inline void push_down(unsigned x, unsigned y, unsigned num, unsigned cnt, bool flag){
    auto tmp = sudoku[x][y];

    if (flag){
        nums[sudoku[x][y] - 'a'] = char(num + '0');
    }

    sudoku[x][y] = char(num + '0');
    row[x] ^= 1u << (num - 1);
    col[y] ^= 1u << (num - 1);
    block[x / 3][y / 3] ^= 1u << (num - 1);

    dfs(cnt - 1);


    if (flag){
        nums[tmp - 'a'] = 0;
    }

    sudoku[x][y] = tmp;
    row[x] ^= 1u << (num - 1);
    col[y] ^= 1u << (num - 1);
    block[x / 3][y / 3] ^= 1u << (num - 1);
}

void dfs(unsigned res){
    if (res == 0){
        for (int i = 'a'; i <= 'z'; i ++){
            if (i == 'e' || i == 'o' || !(tags[i].size())) {continue;}
            auto tmp = sudoku[tags[i][0].first][tags[i][0].second];
            for (auto j : tags[i]){
                if (sudoku[j.first][j.second] != tmp){
                    return;
                }
            }
        }
        ans ++;
        return;
    }

    unsigned x, y, min_state, min_ = INT_MAX;

    for (int i = 0; i < 9; i ++){
        for (int j = 0; j < 9; j ++){
            if ('1' <= sudoku[i][j] && sudoku[i][j] <= '9'){
                continue;
            }
            unsigned now_state = row[i] & col[j] & block[i / 3][j / 3];
            if (ones[now_state] < min_){
                min_ = ones[now_state];
                min_state = now_state;
                x = i, y = j;
            }
        }
    }

    for (int i = 0; i < 9; i++) {
        nums[sudoku[x][y]] = char(i + '0');

        while (min_state) {
            auto lowbit = min_state & -min_state;
            auto num = unsigned(log2(lowbit) + 1);

            if (sudoku[x][y] == '0'){
                push_down(x, y, num, res, false);
            }

            if (sudoku[x][y] >= 'a' && sudoku[x][y] <= 'z' && sudoku[x][y] != 'e' && sudoku[x][y] != 'o') {
                if (nums[sudoku[x][y] - 'a'] == 0) {
                    push_down(x, y, num, res, true);
                }
                else if (num + '0' == nums[sudoku[x][y]]) {
                    push_down(x, y, num, res, false);
                    return;
                }
            }

            if (sudoku[x][y] == 'e' && !(num % 2) || sudoku[x][y] == 'o' && (num % 2)){
                push_down(x, y, num, res, false);
            }

            min_state -= lowbit;
        }
    }
}

int main(){
    for (unsigned i = 0; i < 1u << 9u; i ++){
        unsigned int j = i;
        while (j){
            ones[i] ++;
            j -= j & - j;
        }
    }

    int T;
    cin >> T;
    while (T--) {
        fill(row, row + 9, (1u << 9u) - 1);
        fill(col, col + 9, (1u << 9u) - 1);
        fill(block[0], block[0] + 9, (1u << 9u) - 1);
        int cnt = 0; ans = 0;

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cin >> sudoku[i][j];
                tags[sudoku[i][j]].emplace_back(make_pair(i, j));
                if (sudoku[i][j] >= '1' && sudoku[i][j] <= '9') {
                    row[i] ^= 1u << unsigned(sudoku[i][j] - '1');
                    col[j] ^= 1u << unsigned(sudoku[i][j] - '1');
                    block[i / 3][j / 3] ^= 1u << unsigned(sudoku[i][j] - '1');
                }
                else {
                    cnt ++;
                }
            }
        }

        dfs(cnt);

        cout << ans << endl;
    }

    return 0;
}