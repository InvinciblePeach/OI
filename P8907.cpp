#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 2e5 + 10;
int n, m, ans;
set<int> g[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        g[min(u, v)].emplace(max(u, v));
    }
    for (int i = 1; i <= n; i++) {
        if (g[i].empty()) continue;
        ans += g[i].size();
        int j = *g[i].begin();
        g[i].erase(g[i].begin());
        if (g[i].size() > g[j].size()) swap(g[i], g[j]);
        for (auto p : g[i]) g[j].emplace(p);
    }
    cout << ans - m << '\n';

    return 0;
}