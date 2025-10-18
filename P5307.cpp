#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e6 + 10, mod = 1e9 + 7;
int r, c, n, blkc;
int a[310][310], d[MAXN], rv[MAXN], dp[2][310][3010], blk[3010];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> r >> c >> n;
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++) cin >> a[i][j];
    for (int i = 1; i <= n; i++) (d[i] = (n - 1) / i + 1) != d[i - 1] ? blk[++blkc] = d[i], rv[d[i]] = blkc : 1;
    dp[1][1][rv[(n - 1) / a[1][1] + 1]] = 1;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            for (int k = 1; k <= blkc; k++) {
                if (i != r) (dp[(i & 1) ^ 1][j][rv[(blk[k] - 1) / a[i + 1][j] + 1]] += dp[i & 1][j][k]) %= mod;
                if (j != c) (dp[i & 1][j + 1][rv[(blk[k] - 1) / a[i][j + 1] + 1]] += dp[i & 1][j][k]) %= mod;
                (i != r || j != c || k != blkc) ? dp[i & 1][j][k] = 0 : 1;
            }
        }
    }
    cout << dp[r & 1][c][blkc] << '\n';

    return 0;
}