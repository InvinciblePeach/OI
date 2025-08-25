#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;
int n, q, w[MAXN], c[MAXN];
int cnt, tot, dfn[MAXN], id[MAXN], fa[MAXN], dep[MAXN], top[MAXN], son[MAXN], siz[MAXN], rt[MAXN];
vector<int> g[MAXN];

void dfs1(int u) {
    siz[u] = 1;
    for (auto v : g[u]) {
        if (v == fa[u]) continue;
        fa[v] = u, dep[v] = dep[u] + 1;
        dfs1(v);
        siz[u] += siz[v];
        if (siz[son[u]] < siz[v]) son[u] = v;
    }
}

void dfs2(int u, int top) {
    dfn[id[u] = ++tot] = u, ::top[u] = top;
    if (son[u]) dfs2(son[u], top);
    for (auto v : g[u]) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

struct Node {
    int mx, sum;
} t[MAXN << 5];
int lc[MAXN << 5], rc[MAXN << 5];

Node merge(const Node &a, const Node &b) { return {max(a.mx, b.mx), a.sum + b.sum}; }

void pushup(int p) { t[p] = merge(t[lc[p]], t[rc[p]]); }

void modify(int &p, int l, int r, int pos, int val) {
    if (!p) p = ++cnt;
    if (l == r) return t[p] = {val, val}, void();

    int mid = (l + r) >> 1;
    if (pos <= mid) modify(lc[p], l, mid, pos, val);
    else modify(rc[p], mid + 1, r, pos, val);
    pushup(p);
}

Node query(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) return t[p];

    Node res = {0, 0};
    int mid = (l + r) >> 1;
    if (L <= mid) res = merge(res, query(lc[p], l, mid, L, R));
    if (R > mid) res = merge(res, query(rc[p], mid + 1, r, L, R));
    return res;
}

Node querypath(int x, int y, int col) {
    Node resx = {0, 0}, resy = {0, 0};
    while (top[x] ^ top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y), swap(resx, resy);
        resx = merge(resx, query(rt[col], 1, n, id[top[x]], id[x]));
        x = fa[top[x]];
    }
    if (dep[x] < dep[y]) swap(x, y), swap(resx, resy);
    resx = merge(resx, query(rt[col], 1, n, id[y], id[x]));
    return merge(resx, resy);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> w[i] >> c[i];
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].emplace_back(v), g[v].emplace_back(u);
    }
    dfs1(1), dfs2(1, 1);
    for (int i = 1; i <= n; i++) modify(rt[c[i]], 1, n, id[i], w[i]);
    while (q --> 0) {
        static string op;
        static int x, y;
        cin >> op >> x >> y;
        if (op == "CC") modify(rt[c[x]], 1, n, id[x], 0), modify(rt[c[x] = y], 1, n, id[x], w[x]);
        else if (op == "CW") modify(rt[c[x]], 1, n, id[x], w[x] = y);
        else if (op == "QS") cout << querypath(x, y, c[x]).sum << '\n';
        else if (op == "QM") cout << querypath(x, y, c[x]).mx << '\n';
    }

    return 0;
}