#include <bits/stdc++.h>

using namespace std;

long long dp[25][25];
int H[25][25] = {0};
int X[] = {0, -2, -1, 1, 2, 2, 1, -1, -2};
int Y[] = {0, 1, 2, 2, 1, -1, -2, -2, -1};
int n, m, x, y;

int main(){
    cin >> n >> m >> x >> y;
    H[x][y] = 1;
    for (int i = 0; i < 9; i++){
        int xi = x + X[i], yi = y + Y[i];
        if (xi <= 25 && xi >= 0 && yi <= 25 && yi >= 0){ H[x + X[i]][y + Y[i]] = 1; }
    }
    dp[0][0] = 1 - H[0][0];
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= m; j++){
            if (H[i][j]){ continue; }
            if (i){
                dp[i][j] += dp[i - 1][j];
            }
            if (j){
                dp[i][j] += dp[i][j - 1];
            }
        }
    }
    cout << dp[n][m] << endl;
    return 0;
}
