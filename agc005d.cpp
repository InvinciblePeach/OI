#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 2010, mod = 924844033;
int n, m, frac[MAXN], dp[MAXN << 1][MAXN], tot, a[MAXN << 1], ans;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    frac[0] = 1;
    for (int i = 1; i <= n; i++) frac[i] = frac[i - 1] * i % mod;
    a[tot = 0] = 1;
    for (int i = 1; i <= (n - m) % m; i++)
        a[tot += (n - m) / m + 1] = 1, a[tot += (n - m) / m + 1] = 1;
    for (int i = 1; i <= m - (n - m) % m; i++)
        a[tot += (n - m) / m] = 1, a[tot += (n - m) / m] = 1;
    dp[0][0] = 1;
    for (int i = 1; i <= tot; i++)
        for (int j = 0; j <= n; j++)
            dp[i][j] = (dp[i - 1][j] + (j ? dp[i - 1 - (!a[i - 1])][j - 1] : 0)) % mod;
    for (int j = 0; j <= n; j++)
        (ans += dp[tot][j] * frac[n - j] % mod * (j & 1 ? -1 : 1)) %= mod;
    cout << (ans + mod) % mod << '\n';

    return 0;
}