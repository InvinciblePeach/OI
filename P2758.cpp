#include <bits/stdc++.h>

using namespace std;

string A, B;
int N, M, dp[2005][2005];

int main(){
    cin >> A >> B;
    N = A.size(), M = B.size();
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i <= N; i++){ dp[i][0] = i; }
    for (int i = 0; i <= M; i++){ dp[0][i] = i; }
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= M; j++){
            dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);
            bool flag = (A[i - 1] != B[j - 1]);
            dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + flag);
        }
    }
    cout << dp[N][M] << endl;
    return 0;
}
