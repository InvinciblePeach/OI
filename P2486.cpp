#include <bits/stdc++.h>
#define lc(x) x << 1
#define rc(x) x << 1 | 1

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;
int n, m, tot, c[MAXN], fa[MAXN], dfn[MAXN], id[MAXN], top[MAXN], siz[MAXN], son[MAXN], dep[MAXN];
vector<int> g[MAXN];

struct Node {
    int l, r;
    int lc, rc, sum;
} t[MAXN << 2];
int tag[MAXN << 2];

void dfs1(int u) {
    siz[u] = 1;
    for (auto v : g[u]) {
        if (v == fa[u]) continue;
        fa[v] = u, dep[v] = dep[u] + 1;
        dfs1(v);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int top) {
    dfn[id[u] = ++tot] = u;
    ::top[u] = top;
    if (son[u]) dfs2(son[u], top);
    for (auto v : g[u]) {
        if (v == son[u] || v == fa[u]) continue;
        dfs2(v, v);
    }
}

Node merge(const Node &a, const Node &b) { return {a.l, b.r, a.lc, b.rc, a.sum + b.sum - (a.rc == b.lc)}; }

void pushup(int p) { t[p] = merge(t[lc(p)], t[rc(p)]); }

void pushdown(int p) {
    if (tag[p]) {
        tag[lc(p)] = t[lc(p)].lc = t[lc(p)].rc = tag[p];
        tag[rc(p)] = t[rc(p)].lc = t[rc(p)].rc = tag[p];
        t[lc(p)].sum = t[rc(p)].sum = 1;
        tag[p] = 0;
    }
}

void build(int p, int l, int r) {
    t[p] = {l, r, 0, 0, 0};
    if (l == r) {
        t[p].lc = t[p].rc = c[dfn[l]];
        t[p].sum = 1;
        return;
    }

    int mid = (l + r) >> 1;
    build(lc(p), l, mid), build(rc(p), mid + 1, r);
    pushup(p);
}

void modify(int p, int l, int r, int c) {
    if (l <= t[p].l && t[p].r <= r) return t[p] = {t[p].l, t[p].r, c, c, 1}, tag[p] = c, void();

    pushdown(p);
    if (l <= t[lc(p)].r) modify(lc(p), l, r, c);
    if (r >= t[rc(p)].l) modify(rc(p), l, r, c);
    pushup(p);
}

Node query(int p, int l, int r) {
    if (l <= t[p].l && t[p].r <= r) return t[p];

    pushdown(p);
    if (r <= t[lc(p)].r) return query(lc(p), l, r);
    if (l >= t[rc(p)].l) return query(rc(p), l, r);
    return merge(query(lc(p), l, r), query(rc(p), l, r));
}

void update(int u, int v, int c) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        modify(1, id[top[u]], id[u], c);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v])
        swap(u, v);
    modify(1, id[v], id[u], c);
}

int getans(int u, int v) {
    Node ansu = {0, 0, 0, 0, 0}, ansv = {0, 0, 0, 0, 0};
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v), swap(ansu, ansv);
        ansu = merge(query(1, id[top[u]], id[u]), ansu);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v])
        swap(u, v), swap(ansu, ansv);
    ansu = merge(query(1, id[v], id[u]), ansu);
    return ansu.sum + ansv.sum - (ansu.lc == ansv.lc);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs1(1), dfs2(1, 1);
    build(1, 1, n);

    while (m --> 0) {
        static char op;
        static int u, v, c;
        cin >> op >> u >> v;
        if (op == 'C') cin >> c, update(u, v, c);
        else cout << getans(u, v) << '\n';
    }

    return 0;
}