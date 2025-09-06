#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 21;
int n, k, dp[MAXN][1 << MAXN], nxt[MAXN][1 << MAXN], res[1 << MAXN];
int len, ans;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> k;
    for (int i = 0; i <= n; i++) {
        static string s;
        cin >> s;
        for (int j = 0; j < (1 << i); j++) dp[i][j] = s[j] - '0';
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (1 << i); j++) {
            int nw = j >> (i - 1) & 1;
            nxt[i][j] = -1;
            for (int k = i - 1; k; k--)
                if ((j >> (k - 1) & 1) ^ nw) {
                    nxt[i][j] = k;
                    break;
                }
        }
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < (1 << i); j++) res[j] = 0;
        for (int j = 0; i + j <= n; j++)
            for (int k = 0; k < (1 << (i + j)); k++) res[k >> j] += dp[i + j][k];
        for (int j = (1 << i) - 1; ~j; j--)
            if (res[j] >= k) ans = j, len = i;
        for (int j = 0; i + j <= n; j++)
            for (int k = 0; k < (1 << (i + j)); k++) {
                int nw = nxt[j][k & ((1 << j) - 1)];
                if (~nw) {
                    int tmp = k & ((1 << nw) - 1);
                    dp[i + nw][((k >> j) << nw) + tmp] += dp[i + j][k];
                }
            }
    }
    for (int i = len - 1; ~i; i--) cout << (ans >> i & 1);
    cout << '\n';
    return 0;
}