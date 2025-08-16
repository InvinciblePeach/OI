#include <bits/stdc++.h>

using namespace std;

int N, A[3005], B[3005], dp[3005][3005];

int main(){
    cin >> N;
    for (int i = 1; i <= N; i++){ cin >> A[i]; }
    for (int i = 1; i <= N; i++){ cin >> B[i]; }
    for (int i = 1; i <= N; i++){
        int _max = 1;
        for (int j = 1; j <= N; j++){
            dp[i][j] = dp[i - 1][j];
            if (B[j - 1] < A[i]){
                _max = max(dp[i - 1][j - 1] + 1, _max);
            }
            if (A[i] == B[j]){
                dp[i][j] = max(dp[i][j], _max);
            }
        }
    }
    int _max = INT_MIN;
    for (int i: dp[N]){
        _max = max(_max, i);
    }
    cout << _max;
    return 0;
}

