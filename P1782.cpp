#include<bits/stdc++.h>

using namespace std;

int N, M, C;
int v[10005], w[10005], m[10005], a[10], b[10], c[10];
int dp[10005] = {0};

int main(){
    cin >> N >> M >> C;
    for (int i = 1; i <= N; i++){
        cin >> v[i] >> w[i] >> m[i];
    }
    for (int i = 1; i <= M; i++){
        cin >> a[i] >> b[i] >> c[i];
    }
    for (int i = 1; i <= N; i++){

        vector<int> bag;
        for (int j = 1; j <= m[i]; j *= 2){
            bag.push_back(j);
            m[i] -= j;
        }
        if (m[i] > 0){
            bag.push_back(m[i]);
        }

        for (auto j : bag){
            for (int k = C; k >= j * v[i]; k--){
                dp[k] = max(dp[k], dp[k - j * v[i]] + j * w[i]);
            }
        }
    }
    C -= dp[C];
    for (int i = 1; i <= M; i++){
        int A = a[i], B = b[i], D = c[i];
        for (int Y = D; Y >= 0; Y--){
            for (int X = 0; X <= Y; X++){
                dp[Y] = max(dp[Y],dp[Y - X] + (A * Y + B) * X + D);
            }
        }
    }
    cout << dp[C];
    return 0;
}
