#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int n, a[MAXN];
ll dp[2];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    dp[1] = LLONG_MIN;
    for (int i = 1; i <= n; i++)
        dp[i & 1] = max(dp[i & 1], dp[(i - 1) & 1] + a[i]);
    cout << dp[n & 1] << '\n';

    return 0;
}