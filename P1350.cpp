#include <bits/stdc++.h>

using namespace std;

const int mod = 100003;
int a, b, c, d, k;
int dp[2005][1005] = {0};

int main() {
    cin >> a >> b >> c >> d >> k;
    for (int i = 1; i <= a + c + 1; i++) {
        dp[i][0] = 1;
    }

    for (int i = a + c; i >= 1; i--) {
        for (int j = 1; j <= k; j++) {
            dp[i][j] = (dp[i + 1][j] + dp[i + 1][j - 1] * ((i <= a ? b + d : d) - (j - 1))) % mod;
        }
    }

    cout << dp[1][k] << endl;

    return 0;
}