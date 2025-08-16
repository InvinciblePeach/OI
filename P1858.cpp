#include <bits/stdc++.h>

using namespace std;

int K, V, N, v[205], w[205], dp[5005][55];

int main(){
    cin >> K >> V >> N;
    for (int i = 1; i <= N; i++){
        cin >> v[i] >> w[i];
    }
    memset(dp, 0x80, sizeof(dp));
    dp[0][1] = 0;
    for (int i = 1; i <= N; i++){
        for (int j = V; j >= v[i]; j--){
            int p1 = 1, p2 = 1;
            int tmp[55];
            for (int k = 1; k <= K; k++){
                if (dp[j][p1] >= dp[j - v[i]][p2] + w[i]){
                    tmp[k] = dp[j][p1];
                    p1++;
                }
                else{
                    tmp[k] = dp[j - v[i]][p2] + w[i];
                    p2++;
                }
            }
            for (int k = 1; k <= K; k++){
                dp[j][k] = tmp[k];
            }
        }
    }
    int sum = 0;
    for (int i = 1; i <= K; i++){
        sum += dp[V][i];
    }
    cout << sum << endl;
    return 0;
}