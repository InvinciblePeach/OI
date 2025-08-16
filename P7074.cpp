#include <bits/stdc++.h>

using namespace std;

int n, m, nums[10005][10005] = {0};
long long up[1005], down[1005], dp[1005] = {0};

int main(){
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            cin >> nums[i][j];
        }
    }

    for (int i = 1; i <= n; i++){
        dp[i] = dp[i - 1] + nums[i][1];
    }

    for (int i = 2; i <= m; i++){
        memset(up, 0x80, sizeof(up));
        memset(down, 0x80, sizeof(down));

        for (int j = 1; j <= n; j++){
            up[j] = max(dp[j], up[j - 1]) + nums[j][i];
        }

        for (int j = n; j >= 1; j--){
            down[j] = max(dp[j], down[j + 1]) + nums[j][i];
        }

        for (int j = 1; j <= n; j++){
            dp[j] = max(up[j], down[j]);
        }
    }

    cout << dp[n] << endl;
    return 0;
}