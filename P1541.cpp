#include <bits/stdc++.h>

using namespace std;

int N, M, dp[45][45][45][45], g[5] = {0}, nums[355];

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> nums[i];
    }
    dp[0][0][0][0] = nums[1];
    for (int i = 1; i <= M; i++) {
        int n;
        cin >> n;
        g[n] += 1;
    }
    for (int h = 0; h <= g[1]; h++)
        for (int i = 0; i <= g[2]; i++)
            for (int j = 0; j <= g[3]; j++)
                for (int k = 0; k <= g[4]; k++){
                    int r = h + 2 * i + 3 * j + 4 * k + 1;
                    if (h){
                        dp[h][i][j][k] = max(dp[h - 1][i][j][k] + nums[r], dp[h][i][j][k]);
                    }
                    if (i){
                        dp[h][i][j][k] = max(dp[h][i - 1][j][k] + nums[r], dp[h][i][j][k]);
                    }
                    if (j){
                        dp[h][i][j][k] = max(dp[h][i][j - 1][k] + nums[r], dp[h][i][j][k]);
                    }
                    if (k){
                        dp[h][i][j][k] = max(dp[h][i][j][k - 1] + nums[r], dp[h][i][j][k]);
                    }
                }
    cout << dp[g[1]][g[2]][g[3]][g[4]] << endl;
    return 0;
}