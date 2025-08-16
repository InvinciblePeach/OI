#include<bits/stdc++.h>

using namespace std;

int n, m, a, w[1005], v[1005], g[1005][1005], t = 0, s[1005] = {0}, dp[1005] = {0};

int main(){
    cin >> m >> n;
    for (int i = 1; i <= n; i++){
        cin >> w[i] >> v[i] >> a;
        s[a]++;
        t = max(t, a);
        g[a][s[a]] = i;
    }
    for (int i = 1; i <= t; i++){
        for (int j = m; j >= 0; j--){
            for (int k = 1; k <= s[i]; k++){
                if (j - w[g[i][k]] >= 0){
                    dp[j] = max(dp[j], dp[j - w[g[i][k]]] + v[g[i][k]]);
                }
            }
        }
    }
    cout << dp[m];
    return 0;
}
