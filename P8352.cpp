#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1010, mod = 1e9 + 7;
int n, k, dp[MAXN][MAXN * 5][6], tmp[MAXN * 5][6], siz[MAXN];
vector<int> g[MAXN];

void dfs(int u, int fa) {
    siz[u] = 1;
    for (int i = 1; i <= k; i++) dp[u][0][i] = 1;
    for (auto v : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
        memset(tmp, 0, sizeof(tmp));
        for (int i = 0; i <= k * siz[u]; i++)
            for (int j = 0; j <= k; j++)
                if (dp[u][i][j])
                    for (int p = 0; p <= k * siz[v]; p++)
                        for (int q = 0; q <= k; q++)
                            (tmp[i + p + q][max(i + j + p, i + p + q) - (i + p + q)] +=
                             dp[u][i][j] * dp[v][p][q] % mod) %= mod;
        memcpy(dp[u], tmp, sizeof(tmp));
        siz[u] += siz[v];
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> k;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= k * n; i++) {
        int ans = 0;
        for (int d = 0; d <= min(i, k); d++) (ans += dp[1][i - d][d]) %= mod;
        cout << ans << '\n';
    }
    return 0;
}