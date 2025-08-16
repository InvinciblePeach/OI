#include <bits/stdc++.h>

using namespace std;

int N, d[35], tree[35][35];
long long dp[35][35];

void VLR(int l, int r){
    if (l > r){ return ; }
    cout << tree[l][r] << ' ';
    if (l == r){ return ; }
    VLR(l, tree[l][r] - 1);
    VLR(tree[l][r] + 1, r);
}

int main(){
    cin >> N;
    for (int i = 1; i <= N; i++){
        cin >> d[i];
    }
    for (int i = 1; i <= N; i++){ dp[i][i] = d[i]; }
    for (int len = 1; len <= N; len ++){
        for (int l = 1; l + len - 1 <= N; l++){
            int r = l + len - 1;
            tree[l][r] = l;
            for (int k = l; k <= r; k++){
                if (k == l){ dp[l][r] = max(dp[l][r], dp[l + 1][r] + d[l]); }
                else if (k == r){ dp[l][r] = max(dp[l][r], dp[l][r - 1] + d[r]); }
                else if (dp[l][r] < dp[l][k - 1] * dp[k + 1][r] + d[k]){
                    dp[l][r] = dp[l][k - 1] * dp[k + 1][r] + d[k];
                    tree[l][r] = k;
                }
            }
        }
    }
    cout << dp[1][N] << endl;
    VLR(1, N);
    return 0;
}
