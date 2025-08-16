#include <bits/stdc++.h>

using namespace std;

int N, dp[605][605], nums[605], ans = INT_MIN;

int main(){
    memset(dp, 0x80, sizeof(dp));
    cin >> N;
    for (int i = 1; i <= N; i++){
        cin >> nums[i];
        nums[i + N] = nums[i];
    }
    for (int i = 1; i <= 2 * N; i++){
        dp[i][i + 1] = 0;
    }
    for (int len = 3; len <= N + 1; len++){
        for(int l = 1; l <= 2 * N - len + 1; l++){
            int r = l + len - 1;
            for (int k = l + 1; k < r; k++){
                dp[l][r] = max(dp[l][r], dp[l][k] + dp[k][r] + nums[l] * nums[k] * nums[r]);
                ans = max(ans, dp[l][r]);
            }
        }
    }
    cout << ans << endl;
    return 0;
}
