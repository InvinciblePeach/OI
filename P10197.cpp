#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 310, INF = 1e6;
int n, k, m, a[MAXN], b[10], L[MAXN], R[MAXN], len[10], dp[MAXN][MAXN][1 << 7], ans, sum[1 << 7];
bitset<MAXN> vis;
vector<int> p{0};

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i], ans += (a[i] << 1);
    for (int i = 2; i <= k + 1; i++) cin >> b[i], vis[b[i]] = 1;
    a[0] = a[b[k + 2] = n + 1] = INF, ans += (INF << 1);
    for (int i = 1; i <= n; i++)
        if (!vis[i]) p.emplace_back(a[i]);
    int K = 0;
    for (int i = 1; i <= k + 1; i++) {
        if (b[i] + 1 == b[i + 1])
            ans += abs(a[b[i]] - a[b[i + 1]]);
        else {
            len[++K] = b[i + 1] - b[i] - 1;
            L[K] = a[b[i]], R[K] = a[b[i + 1]];
            if (L[K] > R[K]) swap(L[K], R[K]);
        }
    }
    sort(p.begin(), p.end());
    int m = p.size() - 1;
    assert(m == n - k);
    for (int j = 0; j < (1 << K); j++)
        for (int i = 1; i <= K; i++)
            if (j >> (i - 1) & 1) sum[j] += len[i];
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i <= m + 1; i++)
        for (int j = 0; j <= m + 1; j++) dp[i][j][0] = 0;
    for (int len = 1; len <= m; len++) {
        for (int l = 1, r = len; r <= m; l++, r++) {
            for (int j = 0; j < (1 << K); j++) {
                dp[l][r][j] = min(dp[l + 1][r][j], dp[l][r - 1][j]);
                if (sum[j] > len) continue;
                if (sum[j] == len) {
                    for (int i = 1; i <= K; i++) {
                        if (j >> (i - 1) & 1) {
                            if (::len[i] == 1 && len == 1)
                                dp[l][r][j] = min(dp[l][r][j], abs(L[i] - p[l]) + abs(R[i] - p[r]));
                            else if (::len[i] > 1)
                                dp[l][r][j] = min(dp[l][r][j], dp[l + 1][r - 1][j ^ (1 << (i - 1))] + abs(L[i] - p[l]) +
                                                                   abs(R[i] - p[r]) + p[r] - p[l]);
                        }
                    }
                }
                for (int s = (j - 1) & j; s; s = (s - 1) & j)
                    dp[l][r][j] = min(dp[l][r][j], dp[l][l + sum[s] - 1][s] + dp[l + sum[s]][r][j ^ s]);
            }
        }
    }
    ans += dp[1][m][(1 << K) - 1];
    ans >>= 1, ans -= (INF << 1);
    cout << ans << '\n';

    return 0;
}