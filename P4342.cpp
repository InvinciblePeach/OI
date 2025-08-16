#include <bits/stdc++.h>

using namespace std;

int ans, n, nums[205], dp[205][205], g[205][205];
char operate[205];

int main(){
    memset(dp, 0x80, sizeof(dp));
    memset(g, 0x3f, sizeof(g));
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> operate[i] >> nums[i];
        operate[i + n] = operate[i];
        nums[i + n] = nums[i];
    }
    for (int i = 1; i <= n * 2; i++){
        dp[i][i] = nums[i];
        g[i][i] = nums[i];
    }
    for (int len = 2; len <= n; len++){
        for (int l = 1; l <= 2 * n - len + 1; l++){
            int r = l + len - 1;
            for (int k = l; k < r; k++){
                if (operate[k + 1] == 't'){
                    dp[l][r] = max(dp[l][r], dp[l][k] + dp[k + 1][r]);
                    g[l][r] = min(g[l][r], g[l][k] + g[k + 1][r]);
                }
                else if(operate[k + 1] == 'x'){
                    dp[l][r] = max({dp[l][r],
                                    dp[l][k] * dp[k + 1][r],   // big * big
                                    g[l][k] * g[k + 1][r],     // small * small
                                    dp[l][k] * g[k + 1][r],    // big * small
                                    g[l][k] * dp[k + 1][r]});  // small * big
                    g[l][r] = min({g[l][r],
                                   dp[l][k] * dp[k + 1][r],    // big * big
                                    g[l][k] * g[k + 1][r],     // small * small
                                    dp[l][k] * g[k + 1][r],    // big * small
                                    g[l][k] * dp[k + 1][r]});  // small * big
                }
            }
        }
    }
    for (int i = 1; i <= n; i++){
        ans = max(ans, dp[i][i + n - 1]);
    }
    cout << ans << endl;
    for (int i = 1; i <= n; i++){
        if (dp[i][i + n - 1] == ans){
            cout << i << ' ';
        }
    }
    return 0;
}
