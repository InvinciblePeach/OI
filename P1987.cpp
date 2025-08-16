#include <bits/stdc++.h>

using namespace std;

int n, k, ans = 0, dp[10005];
pair<int, int> trees[1005]; // NOLINT

int main(){
    while (true) {
        cin >> n >> k;
        if (n == 0 && k == 0) { break;}

        memset(dp, 0, sizeof(dp));

        for (int i = 1; i <= n; i++) {
            cin >> trees[i].second;
        }
        for (int i = 1; i <= n; i++) {
            cin >> trees[i].first;
        }

        sort(trees + 1, trees + n + 1, greater<>());

        for (int i = 1; i <= n; i++) {
            for (int j = k; j >= 1; j--) {
                dp[j] = max(dp[j], dp[j - 1] + max(0, trees[i].second - trees[i].first * (j - 1)));
            }
        }

        ans = 0;
        for (int i = 1; i <= k; i++) {
            ans = max(ans, dp[i]);
        }

        cout << ans << endl;
    }
    return 0;
}