#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e5 + 10, mod = 1e9 + 7;
int n, m, ans, u[MAXN], v[MAXN], deg[MAXN], dp[MAXN][2];
bitset<MAXN> vis;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        if (b >>= 1) (a *= a) %= mod;
    }
    return res;
}

int inv(int x) { return x > 0 ? qpow(x, mod - 2) : 1; }

vector<pii> g[MAXN];

void dfs(int u, int fa) {
    dp[u][0] = dp[u][1] = 0;
    int sum = 0;
    for (auto [v, id] : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
        if (id) dp[v][1] += dp[v][0], dp[v][0] = 0;
        (sum += dp[v][1] * (dp[u][0] + dp[u][1]) % mod + dp[v][0] * dp[u][1] % mod) %= mod;
        (dp[u][0] += dp[v][0]) %= mod, (dp[u][1] += dp[v][1]) %= mod;
    }
    int tmp = inv(deg[u] - 1);
    (ans += sum * tmp % mod) %= mod;
    if (deg[u] == 1) dp[u][0]++;
    (dp[u][0] *= tmp) %= mod;
    (dp[u][1] *= tmp) %= mod;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int c, T;
    cin >> c >> T;
    while (T-- > 0) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) vis[i] = deg[i] = 0, g[i].clear();
        for (int i = 1; i < n; i++) cin >> u[i] >> v[i], deg[u[i]]++, deg[v[i]]++;
        for (int i = 1, j; i <= m; i++) cin >> j, vis[j] = 1;
        if (n == 2) {
            cout << "1\n";
            continue;
        }
        for (int i = 1; i < n; i++) {
            g[u[i]].emplace_back(v[i], vis[i]);
            g[v[i]].emplace_back(u[i], vis[i]);
        }
        ans = 0;
        int rt = 0;
        for (int i = 1; i <= n; i++)
            if (deg[i] > 1) rt = i;
        dfs(rt, 0);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j < deg[i]; j++) (ans *= j) %= mod;
        cout << ans << '\n';
    }

    return 0;
}