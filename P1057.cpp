#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

LL n, m;
LL dp[35][35];

int main() {
    cin >> n >> m;
    dp[0][1] = 1;
    for (int i = 1; i <= m; i ++) {
        for (int j = 0; j <= n; j ++) {
            dp[i][j] = dp[i - 1][(j - 1 + n) % n] + dp[i - 1][(j + 1) % n];
        }
    }
    cout << dp[m][1] << endl;
    return 0;
}