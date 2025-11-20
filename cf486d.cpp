#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 2010, mod = 1e9 + 7;
int n, d, ans, a[MAXN], dp[MAXN];
vector<int> g[MAXN];

void dfs(int u, int fa, int rt) {
    dp[u] = 1;
    for (auto v : g[u])
        if ((v ^ fa) && (a[v] < a[rt] || (a[v] == a[rt] && v < rt)) && (a[rt] - a[v] <= d))
            dfs(v, u, rt), (dp[u] *= dp[v] + 1) %= mod;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> d >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    for (int i = 1; i <= n; i++) dfs(i, 0, i), (ans += dp[i]) %= mod;
    cout << ans << '\n';

    return 0;
}