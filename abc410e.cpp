#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3010;
int N, H, M, A[MAXN], B[MAXN];

int main() {
    int N, H, M;
    cin >> N >> H >> M;
    for (int i = 0; i < N; ++i) cin >> A[i] >> B[i];

    vector<vector<int>> dp(H + 1, vector<int>(M + 1, -1));
    dp[H][M] = 0;

    for (int k = 0; k < N; ++k) {
        vector<vector<int>> ndp = dp;
        for (int h = 0; h <= H; ++h) {
            for (int m = 0; m <= M; ++m) {
                if (dp[h][m] == -1) continue;
                if (h >= A[k]) ndp[h - A[k]][m] = max(ndp[h - A[k]][m], dp[h][m] + 1);
                if (m >= B[k]) ndp[h][m - B[k]] = max(ndp[h][m - B[k]], dp[h][m] + 1);
            }
        }
        dp = move(ndp);
    }

    int ans = 0;
    for (int i = 0; i <= H; i++)
        for (int j = 0; j <= M; j++)
            ans = max(ans, dp[i][j]);

    cout << ans << '\n';
    return 0;
}