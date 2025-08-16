#include <bits/stdc++.h>

using namespace std;

unsigned long long N, M, dp[1005][1005] = {0};
bool m[1005][1005] = {false};

int main(){
    dp[1][0] = 1;
    cin >> N >> M;
    for (int i = 1; i <= M; i++){
        int x, y;
        cin >> x >> y;
        m[x][y] = true;
    }

    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            if (!m[i][j]){
                dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % 100003ull;
            }
        }
    }

    cout << dp[N][N] << endl;
    return 0;
}