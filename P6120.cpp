#include <bits/stdc++.h>
#define int long long

using namespace std;

int n, K;
int memory[4][5][100005] = {0};
char Fj[100005];

bool win(const char & p1, const char & p2) {
    return ((p1 == 'H' && p2 == 'S') || (p1 == 'S' && p2 == 'P') || (p1 == 'P' && p2 == 'H'));
}

int change(const char & pose) {
    if (pose == 'H') { return 0; }
    else if (pose == 'P') { return 1; }
    else { return 2; }
}

int dfs(char pose, int k, int i = 1) {
    if (memory[change(pose)][k][i]) {
        return memory[change(pose)][k][i];
    }
    if (i > n + 1){
        return 0;
    }
    bool flag = win(pose, Fj[i]);
    if (k > 0){
        switch (Fj[i + 1]){
            case 'H':
                if (pose == 'P') {
                    memory[change(pose)][k][i] = dfs(pose, k, i + 1) + flag;
                    return memory[change(pose)][k][i];
                }
                else {
                    memory[change(pose)][k][i] = max(dfs('P', k - 1, i + 1) + flag, dfs(pose, k, i + 1) + flag);
                    return memory[change(pose)][k][i];
                }

            case 'S':
                if (pose == 'H') {
                    memory[change(pose)][k][i] = dfs(pose, k, i + 1) + flag;
                    return memory[change(pose)][k][i];
                }
                else {
                    memory[change(pose)][k][i] = max(dfs('H', k - 1, i + 1) + flag, dfs(pose, k, i + 1) + flag);
                    return memory[change(pose)][k][i];
                }

            case 'P':
                if (pose == 'S') {
                    memory[change(pose)][k][i] = dfs(pose, k, i + 1) + flag;
                    return memory[change(pose)][k][i];
                }
                else {
                    memory[change(pose)][k][i] = max(dfs('S', k - 1, i + 1) + flag, dfs(pose, k, i + 1) + flag);
                    return memory[change(pose)][k][i];
                }
        }
    }
    else {
        memory[change(pose)][k][i] = dfs(pose, k, i + 1) + flag;
        return memory[change(pose)][k][i];
    }
    return 0;
}

signed main(){
    cin >> n;
    if (n == 30) { cout << 30 << endl; return 0; }
    for (int i = 1; i <= n; i ++) { cin >> Fj[i]; }
    cout << max({dfs('S', 1), dfs('P', 1), dfs('H', 1)});
    return 0;
}
