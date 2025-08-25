#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 10;
int n, d, ans, cnt[MAXN], dp[MAXN][2];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> d;
    for (int i = 1, a; i <= n; i++) {
        cin >> a;
        cnt[a]++;
    }
    if (d == 0) {
        for (int i = 0; i < MAXN; i++)
            ans += bool(cnt[i]);
        cout << n - ans << '\n';
        return 0;
    }
    
    for (int i = MAXN - 1; ~i; i--) {
        dp[i][0] = cnt[i];
        if (i + d < MAXN) {
            dp[i][0] += min(dp[i + d][1], dp[i + d][0]);
            dp[i][1] += dp[i + d][0];
        }
    }

    for (int i = 0; i < d; i++)
        ans += min(dp[i][0], dp[i][1]);
    cout << ans << '\n';

    return 0;
}