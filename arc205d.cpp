#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 5e5 + 10;
int T, n, top, ans, dp[MAXN];
vector<int> g[MAXN];

void dfs(int u) {
    int sum = 0, mx = 0;
    for (auto v : g[u]) {
        dfs(v);
        sum += dp[v], mx = max(mx, dp[v]);
    }
    int tmp = min(sum - mx, sum >> 1);
    ans += tmp;
    dp[u] = sum - (tmp << 1) + 1;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for (int i = 1; i <= n; i++) g[i].clear();
        for (int i = 2, p; i <= n; i++) {
            cin >> p;
            g[p].emplace_back(i);
        }

        ans = 0;
        dfs(1);
        cout << ans << '\n';
    }
    return 0;
}
