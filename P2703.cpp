#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e6 + 10, INF = 0x3f3f3f3f;
int n, l[MAXN], r[MAXN], dp[2][MAXN][2], top[2], st[2][MAXN], ans;

void solve(int *a) {
    memset(dp, 0x3f, sizeof(dp));
    top[1] = 0;
    for (int j = 1; j <= 3; j++)
        for (int k = a[j]; k <= a[j] + 2; k++)
            if (k >= a[1]) st[1][++top[1]] = k;
    for (int i = 1; i <= top[1]; i++) dp[1][i][0] = st[1][i] - a[1];
    for (int i = 2, nw = 0; i <= n; i++, top[nw ^= 1] = 0) {
        int L = max(1, i - 2), R = min(n, i + 2);
        for (int j = L; j <= R; j++)
            for (int k = a[j]; k <= a[j] + 2; k++)
                if (k >= a[i]) st[nw][++top[nw]] = k;
        for (int j = 1; j <= top[nw]; j++) {
            dp[nw][j][0] = dp[nw][j][1] = INF;
            for (int k = 1; k <= top[nw ^ 1]; k++) {
                if (st[nw ^ 1][k] > st[nw][j])
                    dp[nw][j][0] = min(dp[nw][j][0], dp[nw ^ 1][k][1]);
                else if (st[nw ^ 1][k] < st[nw][j])
                    dp[nw][j][1] = min(dp[nw][j][1], dp[nw ^ 1][k][0]);
                else
                    dp[nw][j][0] = min(dp[nw][j][0], dp[nw ^ 1][k][0]),
                    dp[nw][j][1] = min(dp[nw][j][1], dp[nw ^ 1][k][1]);
            }
            dp[nw][j][0] += st[nw][j] - a[i], dp[nw][j][1] += st[nw][j] - a[i];
        }
    }
    int mn = INF;
    for (int i = 1; i <= top[n & 1]; i++) mn = min(mn, dp[n & 1][i][0]);
    ans += mn;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    int mx = 0;
    for (int i = 1; i <= n; i++) cin >> l[i] >> r[i], mx = max(mx, r[i]);
    solve(r);
    for (int i = 1; i <= n; i++) l[i] = mx - l[i];
    solve(l);
    cout << ans << '\n';

    return 0;
}