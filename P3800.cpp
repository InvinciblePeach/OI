#include <bits/stdc++.h>

using namespace std;

int n, m, k, t, v[4005][4005], dp[4005][4005];

int main() {
    cin >> n >> m >> k >> t;
    for (int i = 1; i <= k; i ++) {
        int x, y, val;
        cin >> x >> y >> val;
        v[x][y] = val;
    }

    for (int i = 1; i <= m; i ++) { dp[1][i] = v[1][i]; }
    for (int i = 2; i <= n; i ++) {
        deque<pair<int, int>> q;
        int r = 0;
        for (int j = 1; j <= m; j ++) {
            while (r < min(j + t, m)) {
                r ++;
                while (!q.empty() && q.back().first <= dp[i - 1][r]) { q.pop_back(); }
                q.emplace_back(dp[i - 1][r], r);
            }
            while (!q.empty() && q.front().second < j - t) { q.pop_front(); }

            dp[i][j] = (!q.empty() ? q.front().first : 0) + v[i][j];
        }
    }

    int max_ = INT_MIN;
    for (int i = 1; i <= m; i ++) { max_ = max(max_, dp[n][i]); }
    cout << max_ << endl;
    return 0;
}