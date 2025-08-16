#include <bits/stdc++.h>

using namespace std;

int n, m, nums[55][55];
int dp[55][55][55][55] = {0};

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            cin >> nums[i][j];
            dp[i][j][i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            for (int k = 1; k <= n; k ++) {
                for (int l = j + 1; l <= m; l ++) {
                    dp[i][j][k][l] = max({dp[i - 1][j][k][l - 1], dp[i][j - 1][k - 1][l], dp[i - 1][j][k - 1][l], dp[i][j - 1][k][l - 1]}) + nums[i][j] + nums[k][l];
                }
            }
        }
    }

    cout << dp[n][m - 1][n - 1][m] << endl;

    return 0;
}