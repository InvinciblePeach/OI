#include<bits/stdc++.h>

using namespace std;

int h, n, v[505], dp[45005] = {0};

int main(){
    cin >> h >> n;
    for (int i = 1; i <= n; i++){
        cin >> v[i];
    }
    for (int i = 1; i <= n; i++){
        for (int j = h; j >= v[i]; j--){
            dp[j] = max(dp[j], dp[j - v[i]] + v[i]);
        }
    }
    cout << dp[h];
    return 0;
}
