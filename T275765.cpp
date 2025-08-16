#include <bits/stdc++.h>

using namespace std;

int n, f[5005], size_[5005], dp[5005];
bool visited[5005];
vector<int> tree[5005];

int build(int x) {
    size_[x] = 1;
    for (auto i = tree[x].begin(); i != tree[x].end(); i ++) {
        if (visited[*i]) { tree[x].erase(i); }
        else { visited[*i] = true; }
        size_[x] += build(*i);
    }
    return size_[x];
}

int dfs(int x, int i, int now_size, int cost) {
    if (i >= tree[x].size()) { return cost + f[now_size]; }
    int ans = dfs(x, i + 1, now_size, cost);
    if (now_size > size_[tree[x][i]]) { ans = min(dfs(x, i + 1, now_size - size_[tree[x][i]] + 1, cost + f[size_[tree[x][i]]]), ans); }
    return ans;
}

void DP(int x) {
    for (auto i : tree[x]) { DP(i); }
    dp[x] = dfs(x, 0, size_[x], 0);
}

int main() {
    cin >> n;
    for (int i = 1; i < n; i ++) { cin >> f[i + 1]; }
    for (int i = 1; i < n; i ++) {
        int u, v;
        cin >> u >> v;
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }
    build(1);
    DP(1);
    cout << dp[1] << endl;
    return 0;
}