#include<bits/stdc++.h>

using namespace std;

int hs, ms, he, me, t;
int n, T, C, P;
int dp[1005];
// 这题数据好好好好好海海海海海海海啊·························
int main(){
    scanf("%d:%d %d:%d", &hs, &ms, &he, &me); // 真的不知道怎么写了，否则不可能用scanf
    t = (he - hs) * 60 - (ms - me);
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> T >> C >> P;
        if (P == 1){
            for (int j = t; j >= T; j--){
                dp[j] = max(dp[j], dp[j - T] + C);
            }
        }
        else if (P == 0){
            for (int j = T; j <= t; j++){
                dp[j] = max(dp[j], dp[j - T] + C);
            }

        }
        else{
            for (int j = t; j >= T; j--){
                for (int k = 1; k <= P && j >= k * T; k++){
                    dp[j] = max(dp[j], dp[j - k * T] + k * C);
                }
            }
        }
    }
    cout << dp[t];
    return 0;
}
