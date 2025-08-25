#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 2010, mod = 1e9 + 7;

int n, dp[MAXN][MAXN][2][2], tmp[MAXN][2][2], siz[MAXN];
vector<int> g[MAXN];

void dfs(int u, int fa) {
    dp[u][0][0][0] = dp[u][1][1][1] = 1;
    siz[u] = 1;
    for (auto v : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
        for (int i = 0; i <= siz[u] + siz[v]; i++) {
            tmp[i][0][0] = 0;
            tmp[i][0][1] = 0;
            tmp[i][1][1] = 0;
        }
        for (int i = siz[u]; ~i; i--) {
            for (int j = siz[v]; ~j; j--) {
                (tmp[i + j][0][0] += dp[u][i][0][0] * (dp[v][j][0][0] + dp[v][j][0][1]) % mod) %= mod;
                if (i >= 1) {
                    (tmp[i + j][0][1] += dp[u][i - 1][0][0] * dp[v][j][1][1] % mod +
                                         dp[u][i][0][1] * (dp[v][j][0][0] + dp[v][j][0][1] + dp[v][j][1][1]) % mod) %= mod;
                    (tmp[i + j][1][1] +=
                     dp[u][i][1][1] * ((j >= 1 ? dp[v][j - 1][0][0] : 0) + dp[v][j][0][1] + dp[v][j][1][1]) % mod) %= mod;
                }
            }
        }
        for (int i = 0; i <= siz[u] + siz[v]; i++) {
            dp[u][i][0][0] = tmp[i][0][0];
            dp[u][i][0][1] = tmp[i][0][1];
            dp[u][i][1][1] = tmp[i][1][1];
        }
        siz[u] += siz[v];
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs(1, 1);
    for (int i = 0; i <= n; i++)
        cout << (dp[1][i][0][0] + dp[1][i][0][1] + dp[1][i][1][1]) % mod << '\n';
    return 0;
}