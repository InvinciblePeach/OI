#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int T, n, m, q, k, tot, cnt, dfn[MAXN], low[MAXN], s[MAXN];
int st[MAXN], top, fa[MAXN][21], dis[MAXN], dep[MAXN], ans;
vector<int> g[MAXN], t[MAXN];

void tarjan(int u) {
    low[u] = dfn[u] = ++tot;
    st[++top] = u;
    for (auto v : g[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                ++cnt;
                do t[st[top]].emplace_back(cnt), t[cnt].emplace_back(st[top]);
                while (st[top--] ^ v);
                t[u].emplace_back(cnt), t[cnt].emplace_back(u);
            }
        } else low[u] = min(low[u], dfn[v]);
    }
}

void dfs(int u) {
    dfn[u] = ++tot;
    for (int j = 1; j <= 20; j++) fa[u][j] = fa[fa[u][j - 1]][j - 1];
    for (auto v : t[u]) {
        if (v == fa[u][0]) continue;
        fa[v][0] = u, dep[v] = dep[u] + 1, dis[v] = dis[u] + (v <= n);
        dfs(v);
    }
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = 20; ~i; i--)
        if (dep[fa[a][i]] >= dep[b]) a = fa[a][i];
    if (a == b) return a;
    for (int i = 20; ~i; i--)
        if (fa[a][i] ^ fa[b][i]) a = fa[a][i], b = fa[b][i];
    return fa[a][0];
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    
    while (T --> 0) {
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(dep, 0, sizeof(dep));
        memset(dis, 0, sizeof(dis));

        cin >> n >> m;
        for (int i = 1, u , v; i <= m; i++) {
            cin >> u >> v;
            g[u].emplace_back(v), g[v].emplace_back(u);
        }
        cnt = n;
        tot = top = 0, tarjan(1);
        tot = 0, dfs(1);

        cin >> q;
        while (q --> 0) {
            cin >> k;
            for (int i = 1; i <= k; i++) cin >> s[i];
            sort(s + 1, s + 1 + k, [](int a, int b) -> bool { return dfn[a] < dfn[b]; });
            ans = -(k << 1);
            for (int i = 1; i <= k; i++) {
                int u = s[i], v = s[i % k + 1];
                ans += dis[u] + dis[v] - (dis[lca(u, v)] << 1);
            }
            if (lca(s[1], s[k]) <= n) ans += 2;
            cout << (ans >> 1) << '\n';
        }
        for (int i = 1; i <= cnt; i++)
            g[i].clear(), t[i].clear();
    }

    return 0;
}