#include <bits/stdc++.h>

using namespace std;

int N, dp[305][305], dp2[305][305], nums[305], sums[305] = {0};

int main(){
    memset(dp, 0x3f, sizeof(dp));
    cin >> N;
    for (int i = 1; i <= N; i++){
        cin >> nums[i];
        sums[i] = sums[i - 1] + nums[i];
        dp[i][i] = 0;
    }
    for (int len = 2; len <= N; len++){
        for(int l = 1; l <= N - len + 1; l++){
            int r = l + len - 1;
            for (int k = l; k < r; k++){
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r]) + (sums[r] - sums[l - 1]);
                dp2[l][r] = max(dp2[l][r], dp2[l][k] + dp2[k + 1][r]) + (sums[r] - sums[l - 1]);
            }
        }
    }
    cout << dp[1][N] << endl;
    cout << dp2[1][N] << endl;
    return 0;
}
