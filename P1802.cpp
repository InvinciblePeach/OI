#include <bits/stdc++.h>

using namespace std;

int n, x, l[1005], w[1005], u[1005];
long long dp[1005];

int main(){
    cin >> n >> x;
    for (int i = 1; i <= n; i++){
        cin >> l[i] >> w[i] >> u[i];
    }
    for (int i = 1; i <= n; i++){
        for (int j = x; j >= u[i]; j--){
            dp[j] = max(dp[j - u[i]] + w[i], dp[j] + l[i]);
        }
        for (int j = u[i] - 1; j >= 0; j--){
            dp[j] += l[i];
        }
    }
    cout << dp[x] * 5 << endl;
    return 0;
}
