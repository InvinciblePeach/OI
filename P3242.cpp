#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 4e4 + 10;
int n, m, q, tot, cnt, lim, c[MAXN], ans[MAXN], fa[MAXN], top[MAXN], dep[MAXN], siz[MAXN], son[MAXN];
int dfn[MAXN], id[MAXN], ed[MAXN], mp[MAXN];
vector<int> g[MAXN];

struct Query {
    int op, x, l, r, k, val, id;

    bool operator<(const Query &o) const {
        if (x == o.x) return id < o.id;
        return x < o.x;
    }
} qry[MAXN], q1[MAXN], q2[MAXN];

struct Fenwick {
    int t[MAXN];

    constexpr int lowbit(const int &x) { return x & -x; }

    void add(int x, int val) {
        for (; x < MAXN; x += lowbit(x)) t[x] += val;
    }

    void add(int l, int r, int val) { add(l, val), add(r + 1, -val); }

    int query(int x) {
        int res = 0;
        for (; x; x -= lowbit(x)) res += t[x];
        return res;
    }
} t;

void dfs1(int u, int fa) {
    siz[u] = 1;
    for (auto v : g[u]) {
        if (v == fa) continue;
        ::fa[v] = u, dep[v] = dep[u] + 1;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int top) {
    dfn[id[u] = ++tot] = u;
    ::top[u] = top;
    if (son[u]) dfs2(son[u], top);
    for (auto v : g[u]) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
    ed[u] = tot;
}

int lca(int x, int y) {
    while (top[x] ^ top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    return x;
}

int getson(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    while (top[x] ^ top[y]) {
        if (fa[top[x]] == y) return top[x];
        x = fa[top[x]];
    }
    return son[y];
}

void solve(int L, int R, int l, int r) {
    if (L > R) return;
    if (l == r) {
        for (int i = L; i <= R; i++)
            if (qry[i].op == 2) ans[qry[i].id] = mp[l];
        return;
    }
    int mid = (l + r) >> 1, cnt1 = 0, cnt2 = 0, val;
    for (int i = L; i <= R; i++) {
        if (qry[i].op == 1) {
            if (qry[i].k <= mid) {
                t.add(qry[i].l, qry[i].r, qry[i].val);
                q1[++cnt1] = qry[i];
            } else q2[++cnt2] = qry[i];
        } else {
            val = t.query(qry[i].l);
            if (val >= qry[i].k) q1[++cnt1] = qry[i];
            else qry[i].k -= val, q2[++cnt2] = qry[i];
        }
    }
    for (int i = 1; i <= cnt1; i++) qry[L + i - 1] = q1[i];
    for (int i = 1; i <= cnt2; i++) qry[L + cnt1 + i - 1] = q2[i];
    solve(L, L + cnt1 - 1, l, mid), solve(L + cnt1, R, mid + 1, r);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> q;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs1(1, 0), dfs2(1, 1);
    for (int i = 1, x, y; i <= m; i++) {
        cin >> x >> y >> mp[i];
        if (id[x] > id[y]) swap(x, y);
        int tmp = lca(x, y);
        if (tmp == x) {
            int z = getson(y, x);
            if (id[z] > 1) {
                qry[++cnt] = {1, 1, id[y], ed[y], mp[i], 1, 0};
                qry[++cnt] = {1, id[z], id[y], ed[y], mp[i], -1, 0};
            }
            if (ed[z] < n) {
                qry[++cnt] = {1, id[y], ed[z] + 1, n, mp[i], 1, 0};
                qry[++cnt] = {1, ed[y] + 1, ed[z] + 1, n, mp[i], -1, 0};
            }
        } else {
            qry[++cnt] = {1, id[x], id[y], ed[y], mp[i], 1, 0};
            qry[++cnt] = {1, ed[x] + 1, id[y], ed[y], mp[i], -1, 0};
        }
    }
    sort(mp + 1, mp + 1 + n);
    lim = unique(mp + 1, mp + 1 + n) - mp - 1;
    for (int i = 1; i <= cnt; i++) qry[i].k = lower_bound(mp + 1, mp + 1 + lim, qry[i].k) - mp;

    for (int i = 1, x, y, k; i <= q; i++) {
        cin >> x >> y >> k;
        if (id[x] > id[y]) swap(x, y);
        qry[++cnt] = {2, id[x], id[y], 0, k, 0, i};
    }
    sort(qry + 1, qry + cnt + 1);
    solve(1, cnt, 1, lim);
    for (int i = 1; i <= q; i++) cout << ans[i] << '\n';

    return 0;
}