#include <bits/stdc++.h>

using namespace std;

int n, m, sum, ans = INT_MIN, a[25];
bool dp[2005];
bool is_delete[25];

void dp_() {
    memset(dp, 0, sizeof(dp));
    int cnt = 0;
    dp[0] = true;

    for (int i = 1; i <= n; i ++) {
        if (is_delete[i]) { continue; }
        for (int j = sum; j >= a[i]; j --) { dp[j] = (dp[j] || dp[j - a[i]]); }
    }

    for (int i = 1; i <= sum; i ++)
        if (dp[i]) { cnt ++; }

    ans = max(ans, cnt);
}

void dfs(int i, int j) {
    if (i > n + 1) { return; }
    if (j == m) { dp_(); return;  }
    dfs(i + 1, j);
    if (j < m) {
        is_delete[i] = true;
        dfs(i + 1, j + 1);
        is_delete[i] = false;
    }
}

int main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        sum += a[i];
    }

    dfs(1, 0);

    cout << ans << endl;

    return 0;
}