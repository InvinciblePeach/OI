#include<bits/stdc++.h>

using namespace std;

int n, r, c, nums[105][105] = {0}, dp[105];

int main(){
    cin >> n;
    for (int _ = 1; _ <= n; _++){
        memset(dp, 0, sizeof(dp));
        cin >> r >> c;
        for (int i = 1; i <= r; i++){
            for (int j = 1; j <= c; j++){
                cin >> nums[i][j];
            }
        }
        for (int i = 1; i <= r; i++){
            for (int j = 1; j <= c; j++){
                dp[j] = max(dp[j - 1] + nums[i][j], dp[j] + nums[i][j]);
            }
        }
        cout << dp[c] << endl;
    }
    return 0;
}
