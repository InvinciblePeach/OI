#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 5e5 + 10;
int T, n, dp[MAXN], siz[MAXN], fa[MAXN];
vector<int> g[MAXN];

int dfs(int u, int val) {
    int mx = 0, son = 0, res = 0;
    if (val >= 1) val--, res++;
    for (auto v : g[u]) {
        if (siz[v] > mx) mx = siz[v], son = v;
    }
    int sum = siz[u] - mx - 1;
    if (mx <= val + sum) return res + ((siz[u] + val - 1) >> 1);
    return res + dfs(son, val + sum);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for (int i = 1; i <= n; i++) g[i].clear(), siz[i] = 1;
        for (int i = 2; i <= n; i++) {
            cin >> fa[i];
            g[fa[i]].emplace_back(i);
        }
        for (int i = n; i; i--) siz[fa[i]] += siz[i];

        cout << dfs(1, 0) << '\n';
    }
    return 0;
}
