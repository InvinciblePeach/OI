#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 5010, mod = 1e9 + 7;
int n, m, cnt[MAXN], dp[2][MAXN][MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, x; i <= n; i++) cin >> x, cnt[x]++;
    dp[0][0][0] = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= cnt[i]; j++) {
            for (int k = 0; k <= min({(i > 1 ? cnt[i - 1] : 0), j, cnt[i + 1]}); k++) {
                if (!dp[i & 1][j][k]) continue;
                (dp[~i & 1][cnt[i + 1] - k][j - k] += dp[i & 1][j][k]) %= mod;
            }
        }
        for (int j = cnt[i + 1]; ~j; j--)
            for (int k = 0; k <= cnt[i + 1]; k++) (dp[~i & 1][j][k] += dp[~i & 1][j + 3][k]) %= mod;
        for (int j = 0; j <= cnt[i]; j++)
            for (int k = 0; k <= cnt[i]; k++) dp[i & 1][j][k] = 0;
    }
    cout << dp[m & 1][0][0] << '\n';

    return 0;
}