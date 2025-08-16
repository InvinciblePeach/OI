#include <bits/stdc++.h>

using namespace std;

int N, K;
int x, y;
int dp[10005][10005];
int nums[10005][10005];

int main() {
    cin >> N >> K;
    for (int i = 1; i <= N; i ++) {
        cin >> x >> y;
        cin >> nums[x][y];
    }

    for (int i = 1; i <= x; i ++) {
        for (int j = 1; j <= y; j ++) {
            for (int k = 1; k <= j; k ++) {
                if (dp[i][k] == -1) {
                    continue;
                } else if (dp[i][k] >= K) {
                    dp[i][j] = max(dp[i][j], dp[i][k] - K);
                }
            }

            for (int k = 1; k <= i; k ++) {
                if (dp[k][j] == -1) {
                    continue;
                } else if (dp[k][j] >= K) {
                    dp[i][j] = max(dp[i][j], dp[k][j] - K);
                }
            }
        }
    }
    cout << dp[x][y] << endl;
    return 0;
}