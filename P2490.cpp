#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e4 + 10, mod = 1e9 + 7;
int n, k, d, ans, dp[15][MAXN], C[MAXN][110];

void init() {
    C[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i && j <= k; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> k >> d;
    init();
    dp[0][0] = 1;
    for (int i = 0, nw = 1; i <= 12; i++, nw <<= 1)
        for (int j = 0; j <= n - k; j++)
            for (int x = 0; j + nw * x * (d + 1) <= n - k && x * (d + 1) <= (k >> 1); x++)
                (dp[i + 1][j + nw * x * (d + 1)] += C[k >> 1][x * (d + 1)] * dp[i][j] % mod) %= mod;
    ans = C[n][k];
    for (int i = 0; i <= n - k; i++) (ans -= dp[13][i] * C[n - i - (k >> 1)][k >> 1] % mod) %= mod;
    cout << (ans % mod + mod) % mod << '\n';

    return 0;
}