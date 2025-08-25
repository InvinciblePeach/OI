#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;
int n, q, dep[MAXN], fa[MAXN][18], tot, id[MAXN];
int st[MAXN], top, siz[MAXN], ans;
vector<int> g[MAXN], t[MAXN];
vector<int> key;

void dfs(int u) {
    id[u] = ++tot;
    for (int i = 1; i < 18; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];

    for (auto v : g[u]) {
        if (v == fa[u][0]) continue;
        dep[v] = dep[u] + 1, fa[v][0] = u;
        dfs(v);
    }
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    int d = dep[a] - dep[b];
    for (int i = 0; d; i++, d >>= 1)
        if (d & 1) a = fa[a][i];
    assert(dep[a] == dep[b]);
    if (a == b) return a;
    
    for (int i = 17; ~i; i--)
        if (fa[a][i] != fa[b][i]) a = fa[a][i], b = fa[b][i];
    return fa[a][0];
}

void insert(int x) {
    if (!top) {
        st[top = 1] = x;
        return;
    }
    int tmp = lca(st[top], x);
    while (top > 1 && dep[tmp] < dep[st[top - 1]]) {
        t[st[top - 1]].emplace_back(st[top]);
        top--;
    }
    if (dep[tmp] < dep[st[top]]) t[tmp].emplace_back(st[top--]);
    if (!top || st[top] != tmp) st[++top] = tmp;
    st[++top] = x;
}

void dfs2(int u) {
    if (siz[u]) {
        for (auto v : t[u]) {
            dfs2(v);
            if (siz[v]) siz[v] = 0, ans++;
        }
    } else {
        for (auto v : t[u]) {
            dfs2(v); 
            siz[u] += siz[v];
            siz[v] = 0;
        }
        if (siz[u] > 1) siz[u] = 0, ans++;
    }
    t[u].clear();
}

void solve() {
    static int m;
    key.clear();
    cin >> m;
    ans = 0;
    for (int i = 1, u; i <= m; i++) {
        cin >> u;
        siz[u] = 1;
        key.emplace_back(u);
    }

    for (auto i : key) {
        if (siz[fa[i][0]]) {
            cout << "-1\n";
            for (auto j : key) siz[j] = 0;
            return;
        }
    }

    sort(key.begin(), key.end(),
         [](const int &a, const int &b) -> bool { return id[a] < id[b]; });

    if (key[0] != 1) st[top = 1] = 1;
    for (auto i : key)
        insert(i);
    if (top) {
        while (--top)
            t[st[top]].emplace_back(st[top + 1]);
    }
    dfs2(1);
    siz[1] = 0;
    cout << ans << '\n';
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