#include <bits/stdc++.h>

using namespace std;

int T, n;
int dp[1005][1005] = {0};
char s[1005] = {0};

int main() {
    cin >> T;
    while (T --> 0) {
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        cin >> n;
        for (int i = 1; i <= n; i ++) {
            cin >> s[i];
        }
        int cnt = 0;
        for (int i = 1; i <= n; i ++) {
            for (int j = 1; j <= i; j ++) {
                if (s[i - 1] == 'P') {

                }
            }
        }
        cout << dp[n] << endl;
    }
    return 0;
}