#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 510;
int n, col[MAXN], num[MAXN], suf[MAXN], dp[MAXN][MAXN][MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> col[i];
    for (int i = 1; i <= n; i++)
        cin >> num[i];
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (col[i] == col[j]) suf[i] += num[j];
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= suf[i]; j++)
            dp[i][i][j] = (num[i] + j) * (num[i] + j);
    for (int len = 2; len <= n; len++) {
        for (int l = 1, r = l + len - 1; r <= n; l++, r++) {
            for (int k = 0; k <= suf[r]; k++) dp[l][r][k] = max(dp[l][r][k], dp[l][r - 1][0] + (num[r] + k) * (num[r] + k));
            for (int i = l; i < r - 1; i++) {
                if (col[i] ^ col[r]) continue;
                for (int k = 0; k <= suf[r]; k++) dp[l][r][k] = max(dp[l][r][k], dp[l][i][num[r] + k] + dp[i + 1][r - 1][0]);
            }
        }
    }
    cout << dp[1][n][0] << '\n';

    return 0;
}