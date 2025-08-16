#include <bits/stdc++.h>
#define int long long

using namespace std;

int n, ans, max_ = LONG_LONG_MIN, dp[1000005], cnt[1000005];
bool visited[1000005];
int depth[1000005];
vector<int> graph[1000005];

void DP1(int i) {
    visited[i] = true;
    cnt[i] = 1;
    dp[i] += depth[i];
    for (auto e : graph[i]) {
        if (visited[e]) { continue; }
        depth[e] = depth[i] + 1;
        DP1(e);
        cnt[i] += cnt[e];
        dp[i] += dp[e];
    }
}

void DP2(int i) {
    if (dp[i] > max_) {
        max_ = dp[i];
        ans = i;
    }
    visited[i] = true;
    for (auto e: graph[i]) {
        if (visited[e]) { continue; }
        dp[e] = dp[i] + n - 2 * cnt[e];
        DP2(e);
    }
}

signed main() {
    cin >> n;
    for (int i = 1; i < n; i ++) {
        int u, v;
        cin >> u >> v;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }

    DP1(1);
    memset(visited, false, sizeof(visited));
    DP2(1);
    cout << ans << endl;
    return 0;
}