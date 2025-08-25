#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e6 + 10, INF = 0x3f3f3f3f;
int n, q, key[MAXN], dep[MAXN], id[MAXN], tot, fa[MAXN][20];
int st[MAXN], top, siz[MAXN], mnans, mxans, mx[MAXN], mn[MAXN];
ll ans, dp[MAXN];
vector<int> g[MAXN], t[MAXN];

void dfs(int u) {
    id[u] = ++tot;
    for (int i = 1; i < 20; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];

    for (auto v : g[u]) {
        if (v == fa[u][0]) continue;
        dep[v] = dep[u] + 1, fa[v][0] = u;
        dfs(v);
    }
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    int d = dep[a] - dep[b];
    for (int i = 0; d; d >>= 1, i++)
        if (d & 1) a = fa[a][i];
    if (a == b) return a;

    for (int i = 19; ~i; i--)
        if (fa[a][i] != fa[b][i]) a = fa[a][i], b = fa[b][i];
    assert(fa[a][0] == fa[b][0]);
    return fa[a][0];
}

void insert(int u) {
    if (!top) return st[top = 1] = 1, void();

    int tmp = lca(st[top], u);
    while (top > 1 && dep[tmp] < dep[st[top - 1]]) {
        t[st[top - 1]].emplace_back(st[top]);
        top--;
    }
    if (dep[tmp] < dep[st[top]]) t[tmp].emplace_back(st[top--]);
    if (!top || st[top] != tmp) st[++top] = tmp;
    st[++top] = u;
}

void dfs2(int u) {
    dp[u] = 0;
    if (siz[u]) mx[u] = mn[u] = 0;
    else mx[u] = -INF, mn[u] = INF;
    for (auto v : t[u]) {
        dfs2(v);
        int w = dep[v] - dep[u];
        ans += (dp[u] + siz[u] * w) * siz[v] + dp[v] * siz[u];
        siz[u] += siz[v], dp[u] += dp[v] + siz[v] * w;
        mnans = min(mnans, mn[u] + mn[v] + w), mxans = max(mxans, mx[u] + mx[v] + w);
        mn[u] = min(mn[u], mn[v] + w), mx[u] = max(mx[u], mx[v] + w);
    }
}

void clear(int u) {
    for (auto v : t[u]) {
        clear(v);
    }
    siz[u] = 0;
    t[u].clear();
}

void solve() {
    static int k;
    ans = 0, mxans = -INF, mnans = INF;
    cin >> k;
    for (int i = 1; i <= k; i++)
        cin >> key[i], siz[key[i]] = 1;

    sort(key + 1, key + 1 + k,
         [](const int &a, const int &b) -> bool { return id[a] < id[b]; });
    if (key[1] != 1) st[top = 1] = 1;
    for (int i = 1; i <= k; i++) insert(key[i]);
    if (top) {
        while (--top)
            t[st[top]].emplace_back(st[top + 1]);
    }
    dfs2(1), clear(1);
    cout << ans << ' ' << mnans << ' ' << mxans << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs(1);

    cin >> q;
    while (q --> 0) solve();

    return 0;
}