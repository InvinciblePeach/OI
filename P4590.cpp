#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1010, mod = 1e9 + 7;
int n, m, a[MAXN], nxt[3][3]{{1, 0, 0}, {1, 2, 0}, {1, 0, 3}}, f[2][MAXN], g[1 << 16][3], dp[2][1 << 16][3], ans[MAXN];
string s;

void init() {
    for (int st = 0; st < (1 << m); st++) {
        for (int k = 1; k <= m; k++) f[0][k] = f[0][k - 1] + (st >> (k - 1) & 1);
        for (int j = 0; j < 3; j++) {
            for (int k = 1; k <= m; k++) {
                f[1][k] = max(f[1][k - 1], f[0][k]);
                if (a[k] == j) f[1][k] = max(f[1][k], f[0][k - 1] + 1);
            }
            int tmp = 0;
            for (int i = 1; i <= m; i++) tmp |= (f[1][i] - f[1][i - 1]) << (i - 1);
            g[st][j] = tmp;
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    cin >> s;
    s = ' ' + s;
    for (int i = 1; i <= m; i++) {
        static map<char, int> mp{{'N', 0}, {'O', 1}, {'I', 2}};
        a[i] = mp[s[i]];
    }
    init();
    dp[0][0][0] = 1;
    for (int i = 0; i < n; i++) {
        memset(dp[(i & 1) ^ 1], 0, sizeof(dp[(i & 1) ^ 1]));
        for (int st = 0; st < (1 << m); st++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    if (j == 2 && k == 2) continue;
                    (dp[(i & 1) ^ 1][g[st][k]][nxt[j][k]] += dp[i & 1][st][j]) %= mod;
                }
            }
        }
    }
    for (int st = 0; st < (1 << m); st++)
        for (int j = 0; j < 3; j++) (ans[__builtin_popcount(st)] += dp[n & 1][st][j]) %= mod;
    for (int i = 0; i <= m; i++) cout << ans[i] << '\n';

    return 0;
}