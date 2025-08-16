#include <bits/stdc++.h>

using namespace std;

const int mod = 10000;
int n, k, dp[1005][1005];

int main() {
    cin >> n >> k;

    dp[1][0] = 1;                                    // 初始化，并不需要枚举每一个 i，DP过程中会计算

    for (int i = 2; i <= n; i ++) {
        int sum = 0;                                 // 前缀和
        for (int j = 0; j <= k; j ++) {
            sum += dp[i - 1][j];
            sum %= mod;
            dp[i][j] = sum;
            if (j - i + 1 >= 0) {
                sum -= dp[i - 1][j - i + 1];
                sum += mod;                          // + mod，防止负数取模
                sum %= mod;
            }
        }
    }

    cout << dp[n][k] % mod /*实际上这里也可以不 % mod，取模也没问题*/ << endl;

    return 0;
}