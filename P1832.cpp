#include <bits/stdc++.h>

using namespace std;

int n;
bool prime[1005] = {false};
long long dp[1005];

int main(){
    cin >> n;

    for (int i = 2; i <= n; i++){
        if (!prime[i]){
            for (int j = 2; i * j <= 1005; j++){
                prime[i * j] = true;
            }
        }
    }

    dp[0] = 1;
    for (int i = 2; i <= n; i++){
        if (!prime[i]){
            for (int j = i; j <= n; j++){
                dp[j] += dp[j - i];
            }
        }
    }

    cout << dp[n] << endl;

    return 0;
}