#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e5 + 10;
int n, tot, a[MAXN], dfn[MAXN], siz[MAXN], res[MAXN], cnt[MAXN];
vector<int> g[MAXN], st[MAXN];
bitset<MAXN> vis;

void dfs1(int u, int fa) {
    const auto &c = a[u];
    siz[u] = 1, dfn[u] = ++tot;
    for (auto v : g[u]) {
        if (v == fa) continue;
        int tmp = cnt[c];
        dfs1(v, u);
        siz[u] += siz[v];
        int nw = siz[v] + tmp - cnt[c];
        cnt[c] += nw;
        res[v] += nw;
        while (!st[c].empty() && dfn[st[c].back()] > dfn[u]) res[st[c].back()] -= nw, st[c].pop_back();
    }
    cnt[c]++;
    st[c].emplace_back(u);
}

void dfs2(int u, int fa) {
    res[u] += res[fa];
    for (auto v : g[u])
        if (v ^ fa) dfs2(v, u);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], vis[a[i]] = 1;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs1(1, 0);
    for (int i = 1; i <= 1e5; i++) {
        if (!vis[i]) continue;
        res[1] += n - cnt[i];
        for (auto v : st[i]) res[v] -= n - cnt[i];
    }
    dfs2(1, 0);
    for (int i = 1; i <= n; i++) cout << n * vis.count() - res[i] << '\n';

    return 0;
}