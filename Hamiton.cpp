#include <bits/stdc++.h>

using namespace std;

unsigned int N, matrix[100005][100005], dp[100005][100005];

int main(){
    cin >> N;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> matrix[i][j];
        }
    }

    memset(dp, 0x3f, sizeof(dp));

    dp[1][0] = 0;
    for (unsigned int visited = 1; visited <= (1u << N) - 1; visited++){
        for (unsigned int now_loc = 0; now_loc <= N - 1; now_loc++){
            if ((visited >> now_loc) & 1u){
                for (unsigned int k = 0; k <= N - 1; k++){
                    if ((visited >> k) & 1u){
                        dp[visited][now_loc] = min(dp[visited][now_loc],dp[visited ^ (1u << now_loc)][k] + matrix[k][now_loc]);
                    }
                }
            }
        }
    }
    cout << dp[(1u << N) - 1][N - 1];
    return 0;
}
