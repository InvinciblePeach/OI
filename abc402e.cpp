#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

const int MAXN = 10, MAXM = 5010;
int n, m, s[MAXN], c[MAXN];
ld p[MAXN], dp[1 << MAXN][MAXM];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> c[i] >> p[i];
        p[i] /= 100;
    }

    for (int t = (1 << n) - 1; ~t; t--) {
        for (int j = 0; j <= m; j++) {
            for (int i = 0; i < n; i++) {
                if ((t >> i & 1) || c[i] > j) continue;
                dp[t][j] = max(p[i] * (dp[t | (1 << i)][j - c[i]] + s[i]) +
                                   (1 - p[i]) * dp[t][j - c[i]],
                               dp[t][j]);
            }
        }
    }
    
    printf("%.6Lf\n", dp[0][m]);

    return 0;
}