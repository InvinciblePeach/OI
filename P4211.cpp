#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 5e4 + 10, mod = 201314;
int n, m, fa[MAXN], ans[MAXN], dep[MAXN], siz[MAXN];
int num, cnt, nw, son[MAXN], top[MAXN], id[MAXN], dfn[MAXN];
vector<int> g[MAXN];

constexpr int ls(int x) { return x << 1; }
constexpr int rs(int x) { return x << 1 | 1; }

struct Query {
    int p, z, id, val;

    Query() {}
    Query(int P, int Z, int Id, int Val) : p(P), z(Z), id(Id), val(Val) {}

    constexpr bool operator<(const Query &o) { return p < o.p; }
} q[MAXN << 1];

struct Node {
    int l, r;
    int sum, tag;
} t[MAXN << 2];

void dfs1(int u) {
    siz[u] = 1;
    for (auto v : g[u]) {
        dep[v] = dep[u] + 1;
        dfs1(v);
        siz[u] += siz[v];
        if (siz[son[u]] < siz[v]) son[u] = v;
    }
}

void dfs2(int u, int tp) {
    top[u] = tp;
    dfn[++num] = u;
    id[u] = num;
    if (!son[u]) return;
    dfs2(son[u], tp);
    for (auto v : g[u]) {
        if (v == son[u]) continue;
        dfs2(v, v);
    }
}

void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    if (l == r) return;

    int mid = (l + r) >> 1;
    build(ls(p), l, mid), build(rs(p), mid + 1, r);
}

void pushup(int p) {
    t[p].sum = (t[ls(p)].sum + t[rs(p)].sum) % mod;
}

void pushdown(int p) {
    (t[ls(p)].sum += t[p].tag * (t[ls(p)].r - t[ls(p)].l + 1) % mod) %= mod;
    (t[rs(p)].sum += t[p].tag * (t[rs(p)].r - t[rs(p)].l + 1) % mod) %= mod;
    (t[ls(p)].tag += t[p].tag) %= mod, (t[rs(p)].tag += t[p].tag) %= mod;
    t[p].tag = 0;
}

void modify(int p, int l, int r, int val) {
    if (l <= t[p].l && t[p].r <= r) {
        (t[p].sum += val * (t[p].r - t[p].l + 1) % mod) %= mod;
        (t[p].tag += val) %= mod;
        return;
    }

    pushdown(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if (l <= mid) modify(ls(p), l, r, val);
    if (r > mid) modify(rs(p), l, r, val);
    pushup(p);
}

int query(int p, int l, int r) {
    if (l <= t[p].l && t[p].r <= r) return t[p].sum;

    pushdown(p);
    int mid = (t[p].l + t[p].r) >> 1, res = 0;
    if (l <= mid) res += query(ls(p), l, r);
    if (r > mid) res += query(rs(p), l, r);
    return res;
}

void modify_chain(int x, int y) {
    int tpx = top[x], tpy = top[y];
    while (tpx != tpy) {
        if (dep[tpx] < dep[tpy]) swap(tpx, tpy), swap(x, y);
        int l = id[tpx], r = id[x];
        modify(1, l, r, 1);
        x = fa[tpx], tpx = top[x];
    }
    if (dep[x] > dep[y]) swap(x, y);
    int l = id[x], r = id[y];
    modify(1, l, r, 1);
}

int query_chain(int x, int y) {
    int tpx = top[x], tpy = top[y], ans = 0;
    while (tpx != tpy) {
        if (dep[tpx] < dep[tpy]) swap(tpx, tpy), swap(x, y);
        int l = id[tpx], r = id[x];
        (ans += query(1, l, r)) %= mod;
        x = fa[tpx], tpx = top[x];
    }
    if (dep[x] > dep[y]) swap(x, y);
    int l = id[x], r = id[y];
    (ans += query(1, l, r)) %= mod;
    return ans;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 2; i <= n; i++) {
        cin >> fa[i];
        g[++fa[i]].emplace_back(i);
    }
    for (int i = 1, l, r, z; i <= m; i++) {
        cin >> l >> r >> z;
        r++, z++;
        q[++cnt] = {l, z, i, -1};
        q[++cnt] = {r, z, i, 1};
    }

    dep[1] = 1;
    dfs1(1);
    dfs2(1, 1);
    build(1, 1, n);

    sort(q + 1, q + 1 + cnt);

    for (int i = 1; i <= cnt; i++) {
        while (nw < q[i].p) modify_chain(1, ++nw);

        (ans[q[i].id] += query_chain(1, q[i].z) * q[i].val) %= mod;
    }
    for (int i = 1; i <= m; i++) cout << (ans[i] + mod) % mod << '\n';

    return 0;
}