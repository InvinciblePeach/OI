#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int T, n;
vector<int> g[MAXN];

void dfs(int u, int fa, int col) {
    if (col)
        cout << fa << ' ' << u << '\n';
    else
        cout << u << ' ' << fa << '\n';
    for (auto v : g[u]) {
        if (v == fa) continue;
        dfs(v, u, col ^ 1);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        cin >> n;
        for (int i = 1; i <= n; i++) g[i].clear();
        for (int i = 1, u, v; i < n; i++) {
            cin >> u >> v;
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        int rt = -1;
        for (int i = 1; i <= n; i++)
            if (g[i].size() == 2) rt = i;
        if (~rt) {
            cout << "YES\n";
            dfs(g[rt][0], rt, 1);
            dfs(g[rt][1], rt, 0);
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}