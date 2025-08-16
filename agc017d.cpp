#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 1e5 + 10;
int n;
vector<int> t[MAXN];

int dfs(int u, int fa) {
    int res = 0;
    for (auto v : t[u]) {
        if (v == fa) continue;
        res ^= dfs(v, u) + 1;
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        t[u].emplace_back(v);
        t[v].emplace_back(u);
    }
    cout << (dfs(1, 0) ? "Alice\n" : "Bob\n");

    return 0;
}