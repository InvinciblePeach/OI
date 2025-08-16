#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 1e6 + 10;
int n, d, ans, fa[MAXN], cnt[MAXN], dp[MAXN][2];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> d;
    for (int i = 1, a; i <= n; i++) {
        cin >> a;
        cnt[a]++;
    }
    if (d == 0) {
        for (int i = 1; i < MAXN; i++)
        ans += bool(cnt[i]);
        cout << n - ans << '\n';
        return 0;
    }

    for (int i = 1; i < MAXN; i++) fa[i] = i;
    
    for (int i = 1e6; i; i--) {
        dp[i][0] = cnt[i];
        if (i + d < MAXN) {
            dp[i][0] += min(dp[i + d][1], dp[i + d][0]);
            dp[i][1] += dp[i + d][0];
            fa[i + d] = i;
        }
    }

    // for (int i = 1; i <= 5; i++) {
    //     cout << fa[i] << ' ' << dp[i][0] << ' ' << dp[i][1] << '\n';
    // }

    for (int i = 1; i < MAXN; i++) {
        if (fa[i] == i && cnt[i]) {
            ans += min(dp[i][0], dp[i][1]);
        }
    }
    cout << ans << '\n';

    return 0;
}