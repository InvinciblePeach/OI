#include <bits/stdc++.h>

using namespace std;

const int mod = 1000000007;
int n;

int main() {
    cin >> n;
    for (int i = int(pow(10, n - 1)); i <= int(pow(10, n) - 1); i++) {
        for (int j = 1; j <= n; j++) {
            int r = lower_bound(dp, dp + j, a[j]) - dp;
            dp[r] = missile[j];
            ans = max(ans, r);
        }

        cout << ans << endl;
    }
    return 0;
}