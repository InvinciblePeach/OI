#include <bits/stdc++.h>

using namespace std;

unsigned int N, M, dp[100005][100005];
bool S[1u << 11u];

int main(){
    cin >> N >> M;
    for (unsigned int i = 0; i <= (1u << N) - 1; i++){
        int cnt = 0;
        bool is_even = true;
        for (unsigned int j = 0; j < N; j++){
            if (i >> j & 1u){
                if (cnt % 2 == 1){
                    is_even = false;
                }
                cnt = 0;
            }
            else{
                cnt++;
            }
        }
        if (cnt % 2 == 1){
            is_even = false;
        }
        S[i] = is_even;
    }
    dp[0][0] = 1;
    for (int i = 1; i <= M; i++){
        for (int j = 0; j < 1u << N; j++){
            for (int k = 0; k < 1u << N; k++){
                dp[i][j] += dp[i - 1][k];
            }
        }
    }
    cout << dp[M][0] << endl;
    return 0;
}
