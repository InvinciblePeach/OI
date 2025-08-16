#include <bits/stdc++.h>

using namespace std;

int n, l, k, dp[6005][2], H[6005], father[6005] = {0};
vector<int> graph[6005];

void DP(int i) {
    dp[i][0] = 0;
    dp[i][1] = H[i];
    if (graph[i].empty()) { return; }
    else {
        for (auto j : graph[i]) {
            DP(j);
            dp[i][0] += max(dp[j][0], dp[j][1]);
            dp[i][1] += dp[j][0];
        }
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> H[i];
    }
    for (int i = 1; i <= n - 1; i++) {
        cin >> l >> k;
        father[l] = k;
        graph[k].push_back(l);
    }
    int root = 0;
    for (int i = 1; i <= n; i++) {
        if (!father[i]) {
            root = i;
            break;
        }
    }
    DP(root);
    cout << max(dp[root][0], dp[root][1]) << endl;
    return 0;
}