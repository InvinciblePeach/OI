#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 510, mod = 998244353;
int n, m, c[MAXN], cnt[MAXN], sum[MAXN], dp[MAXN][MAXN][MAXN], C[MAXN][MAXN], ans, frac[MAXN];
char s[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> s[i];
    for (int i = 1; i <= n; i++) cin >> c[i], cnt[c[i]]++;
    sum[0] = cnt[0];
    for (int i = 1; i <= n; i++) sum[i] = (sum[i - 1] + cnt[i]) % mod;
    frac[0] = 1;
    for (int i = 1; i <= n; i++) frac[i] = frac[i - 1] * i % mod;
    C[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    dp[0][0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            for (int k = 0; k <= i; k++) {
                if (s[i + 1] == '1') {
                    for (int p = 0; p <= cnt[j + 1]; p++)
                        if (p <= k && i - k < sum[j])
                            (dp[i + 1][j + 1][k - p] += dp[i][j][k] * (sum[j] - i + k) % mod * C[k][p] % mod *
                                                        C[cnt[j + 1]][p] % mod * frac[p] % mod) %= mod;

                    (dp[i + 1][j][k + 1] += dp[i][j][k]) %= mod;
                } else {
                    for (int p = 0; p <= cnt[j + 1]; p++) {
                        if (p <= k && i - k + p < sum[j + 1])
                            (dp[i + 1][j + 1][k - p] += dp[i][j][k] * (sum[j + 1] - i + k - p) % mod * C[k][p] % mod *
                                                        C[cnt[j + 1]][p] % mod * frac[p] % mod) %= mod;
                        if (p <= k)
                            (dp[i + 1][j + 1][k - p + 1] +=
                             dp[i][j][k] * C[k][p] % mod * C[cnt[j + 1]][p] % mod * frac[p] % mod) %= mod;
                    }
                }
            }
        }
    }
    for (int j = 0; j <= n - m; j++) (ans += dp[n][j][n - sum[j]] * frac[n - sum[j]] % mod) %= mod;
    cout << (ans + mod) % mod << '\n';

    return 0;
}