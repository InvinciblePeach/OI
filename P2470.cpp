#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 110;
int n, dp[MAXN][MAXN][2];
string s;

bool check(int l, int r) {
    if ((r - l - 1) & 1) return false;
    int mid = (l + r) >> 1;
    for (int i = 1; mid + i <= r; i++)
        if (s[l + i - 1] ^ s[mid + i]) return false;
    return true;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> s;
    n = s.size();
    s = ' ' + s;
    for (int i = n; i; i--) {
        for (int j = i; j <= n; j++) {
            dp[i][j][0] = dp[i][j][1] = j - i + 1;
            for (int k = i; k < j; k++) dp[i][j][0] = min(dp[i][j][0], dp[i][k][0] + j - k);
            for (int k = i; k < j; k++)
                dp[i][j][1] =
                    min(dp[i][j][1], min(dp[i][k][0], dp[i][k][1]) + 1 + min(dp[k + 1][j][0], dp[k + 1][j][1]));
            if (check(i, j)) dp[i][j][0] = min(dp[i][j][0], dp[i][(i + j) >> 1][0] + 1);
        }
    }
    cout << min(dp[1][n][0], dp[1][n][1]) << '\n';

    return 0;
}