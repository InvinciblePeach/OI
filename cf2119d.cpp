#include <bits/stdc++.h>
#define int long long

using namespace std;
const int MAXN = 5010;
int T, n, m;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    vector<pair<int, int>> qs(T);
    int N = 0;
    for (int i = 0; i < T; i++) {
        cin >> qs[i].first >> qs[i].second;
        N = max(N, qs[i].first);
    }

    for (auto [n, mod] : qs) {
        vector<int> dp(n + 1), ndp(n + 1);
        dp[0] = 1;

        vector<int> pre(n + 1), suf(n + 1);

        for (int i = 1; i <= n; i++) {
            fill(ndp.begin(), ndp.end(), 0);
            fill(suf.begin(), suf.end(), 0);
            int sum_i = (int)(i) * (i + 1) / 2 % mod;

            for (int k = 0; k <= i; k++) {
                if (k <= i - 1) {
                    ndp[k] = (ndp[k] + dp[k]) % mod;
                    suf[k] = (suf[k] + pre[k]) % mod;
                }
                if (k >= 1) {
                    int ways = ((sum_i - pre[k - 1]) % mod + mod) % mod;
                    ndp[k] = (ndp[k] + dp[k - 1] * ways) % mod;
                    suf[k] = (suf[k] + pre[k - 1] * ways % mod + dp[k - 1] * ways % mod) % mod;
                }
            }
            swap(dp, ndp);
            swap(pre, suf);
        }

        int ans = 0;
        for (int k = 0; k <= n; k++) {
            ans = (ans + dp[k]) % mod;
        }
        cout << ans << "\n";
    }
    return 0;
}