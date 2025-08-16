#include <bits/stdc++.h>

using namespace std;

const int mod = 100003;
int n, k;
int dp[100005];

int main() {
    cin >> n >> k;
    dp[0] = 1;
    for (int i = 0; i <= n; i++) {
        for (int j = max(0, i - k); j < i; j++) {
            dp[i] += dp[j];
            dp[i] %= mod;
        }
    }
    cout << dp[n] << endl;
    return 0;
}