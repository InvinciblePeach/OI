#include<bits/stdc++.h>

using namespace std;

int N, V, v[1005], k, dp[1005][1005], t[1005][1005], w[1005], path[1005], tmp[1005];

int main(){
    memset(dp, 0x80, sizeof(dp));
    dp[0][1] = 0;
    for (int i = 1; i <= N; i++){
        for (int j  = V; j >= v[i]; j--){
            int p1 = 1, p2 = 1;
            for (int l = 1; l <= k; l++){
                if (dp[i][p1] >= dp[j - v[i]][p2] + w[i]){
                    tmp[l] = dp[j][p1];
                    p1++;
                }
                else{
                    tmp[l] = dp[j - v[i]][p2] + w[i];
                    p2++;
                }
            }
            for (int l = 1; l <= N; l++){
                dp[j][l] = tmp[l];
            }
        }
    }
    for (int i = 1; i <= k; i++){
        cout << dp[V][i] << endl;
    }
    return 0;
}
