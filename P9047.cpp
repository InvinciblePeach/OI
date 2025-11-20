#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
const int MAXN = 2e5 + 10, MAXV = 1010, S = 500;
int n, dp[MAXN][4], f[MAXV][2], h[MAXV][2];
vector<pii> g[MAXN];

void dfs(int u, int fa) {
    for (auto [v, w] : g[u])
        if (v ^ fa) dfs(v, u);
    shuffle(g[u].begin(), g[u].end(), rnd);
    memset(f, -0x3f, sizeof(f));
    memset(h, -0x3f, sizeof(h));
    int l = S, r = S;
    f[l][0] = h[l][0] = 0;
    for (auto [v, w] : g[u]) {
        if (v == fa) continue;
        l = max(1ll, l - 1), r = min(S << 1, r + 1);
        for (int i = l; i <= r; i++) {
            for (int j = 0; j <= 1; j++) {
                f[i][j] = h[i][j] + dp[v][0];
                f[i][j] = max(f[i][j], h[i][j] + w + dp[v][3]);
                f[i][j] = max(f[i][j], h[i - 1][j] + w + dp[v][0]);
                f[i][j] = max(f[i][j], h[i + 1][j] + w + dp[v][2]);
                f[i][j] = max(f[i][j], h[i][j ^ 1] + w + dp[v][1]);
            }
        }
        memcpy(h, f, sizeof(f));
    }
    dp[u][0] = f[S][0], dp[u][1] = f[S + 1][0], dp[u][2] = f[S][1], dp[u][3] = f[S - 1][0];
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1, u, v, w; i < n; i++) {
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    dfs(1, 0);
    cout << dp[1][0] << '\n';

    return 0;
}