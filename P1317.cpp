#include <bits/stdc++.h>

using namespace std;

int S;
int nums[1005], dp[1005];

int main(){
    cin >> S;
    for (int i = 1; i <= S / 2 + 1; i++){
        for (int j = 2; i * j <= S; j++){
            nums[i * j] += i;
        }
    }
    for (int i = 1; i <= S; i++){
        for (int j = S; j >= i; j--){
            dp[j] = max(dp[j - i] + nums[i], dp[j]);
        }
    }
    cout << dp[S];
    return 0;
}