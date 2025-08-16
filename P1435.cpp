#include <bits/stdc++.h>

using namespace std;

string s;
char A[1001], B[1001];
int N, dp[1005][1005] = {0};

int main(){
    cin >> s;
    N = s.size();
    for (int i = 1; i <= N; i++){
        A[i] = s[i - 1];
        B[N - i + 1] = s[i - 1];
    }
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            if (A[i] == B[j]){
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            }
            dp[i][j] = max({dp[i][j], dp[i - 1][j], dp[i][j - 1]});
        }
    }
    cout << N - dp[N][N] << endl;
    return 0;
}
