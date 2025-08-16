#include <bits/stdc++.h>

using namespace std;

int n, s, ans;
int a[100005], dp[100005];
vector<int> tree[100005];

void DP(int x, int father) {
    dp[x] = dp[father] + a[x];
    for (auto i : tree[x]) {
        DP(i, x);
    }
}

void dfs(int x, int begin) {
    int now_s = dp[x] - dp[begin] + a[begin];
//    cout << x << ' ' << begin << ' ' << now_s << endl;
    if (now_s == s) { ans ++; return; }
    else if (now_s > s) { return; }

    for (auto i : tree[x]) {
        dfs(i, begin);
    }
}

int main() {
    cin >> n >> s;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    for (int i = 1; i < n; i ++) {
        int x, y;
        cin >> x >> y;
        tree[x].emplace_back(y);
    }

    DP(1, 0);

    for (int i = 1; i <= n; i ++) {
        dfs(i, i);
    }

    cout << ans << endl;

    return 0;
}