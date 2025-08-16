#include <bits/stdc++.h>

using namespace std;

const int mod = 100000000;
int n, m;
int dp[2][5005], f[2][5005];
string a, b;

int main() {
    cin >> a >> b;
    n = int(a.size()) - 1;
    m = int(b.size()) - 1;
    a = " " + a.substr(0, n);
    b = " " + b.substr(0, m);

    for (int i = 0; i <= m; i++) {
        f[0][i] = 1;
    }
    f[1][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            f[i % 2][j] = 0;
            if (a[i] == b[j]) {
                dp[i % 2][j] = max(dp[i % 2][j], dp[(i - 1) % 2][j - 1] + 1);
                f[i % 2][j] += f[(i - 1) % 2][j - 1];
            } else {
                dp[i % 2][j] = max(dp[(i - 1) % 2][j], dp[i % 2][j - 1]);
            }

            if (dp[i % 2][j] == dp[(i - 1) % 2][j]) {
                f[i % 2][j] += f[(i - 1) % 2][j];
            }

            if (dp[i % 2][j] == dp[i % 2][j - 1]) {
                f[i % 2][j] += f[i % 2][j - 1];
            }

            if (dp[i % 2][j] == dp[(i - 1) % 2][j - 1] && a[i] != b[j]) {
                f[i % 2][j] -= f[(i - 1) % 2][j - 1];
            }

            f[i % 2][j] %= mod;
        }
    }

    cout << dp[n % 2][m] << endl;
    cout << f[n % 2][m] << endl;
    return 0;
}