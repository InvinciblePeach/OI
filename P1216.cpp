#include <bits/stdc++.h>

using namespace std;

int r, nums[1005][1005], dp[1005][1005] = {0};

int main(){
    cin >> r;

    for (int i = 1; i <= r; i++){
        for (int j = 1; j <= i; j++){
            cin >> nums[i][j];
        }
    }

    for (int i = 1; i <= r; i++){
        for (int j = 1; j <= i; j++){
            dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j]) + nums[i][j];
        }
    }

    int ans = INT_MIN;
    for (int i = 1; i <= r; i++){
        ans = max(ans, dp[r][i]);
    }

    cout << ans;
    return 0;
}