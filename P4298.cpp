#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 110, MAXM = 1010;
int n, m, match[MAXN];
bitset<MAXN> g[MAXN], vis, del;

bool dfs(int u) {
    if (!u) return true;
    for (int v = 1; v <= n; v++) {
        if (g[u][v] && !vis[v] && !del[v]) {
            vis[v] = 1;
            if (!match[v] || dfs(match[v])) return match[v] = u, true;
        }
    }
    return false;
}

int col[MAXN];
bitset<MAXN> can, res;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        g[u][v] = 1;
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            if (g[i][k]) g[i] |= g[k];
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        vis.reset();
        if (dfs(i)) cnt++;
    }
    int ans;
    cout << (ans = n - cnt) << '\n';
    for (int i = 1; i <= n; i++) {
        memset(match, 0, sizeof(match));
        del.reset();
        int cnt = 0, tot = n;
        for (int j = 1; j <= n; j++)
            if (g[i][j] || g[j][i] || i == j) tot--, del[j] = 1;
        for (int j = 1; j <= n; j++) {
            if (del[j]) continue;
            vis.reset();
            if (dfs(j)) cnt++;
        }
        can[i] = (tot - cnt == ans - 1);
    }
    int num = 0;
    for (int i = 1; i <= n; ++i) {
        if (can[i] && !col[i]) {
            num++;
            res[i] = 1;
            for (int j = 1; j <= n; ++j)
                if (g[j][i] || g[i][j] || j == i) col[j] = num;
        }
    }
    for (int i = 1; i <= n; i++) cout << res[i];
    cout << '\n';
    for (int i = 1; i <= n; i++) cout << can[i];
    cout << '\n';

    return 0;
}