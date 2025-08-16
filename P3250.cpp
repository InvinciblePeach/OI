#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 2e5 + 10;
int n, m, tot, dfn[MAXN], id[MAXN], fa[MAXN], top[MAXN], son[MAXN], dep[MAXN], siz[MAXN];
int a[MAXN], b[MAXN], val[MAXN], ans[MAXN];
vector<int> g[MAXN];

struct Fenwick {
    int t[MAXN];

    constexpr int lowbit(const int &x) { return x & -x; }

    void add(int x, int val) {
        for (; x <= n; x += lowbit(x)) t[x] += val;
    }

    int query(int x) {
        int res = 0;
        for (; x; x -= lowbit(x)) res += t[x];
        return res;
    }

    int query(int l, int r) { return query(r) - query(l - 1); }
} fwk;

struct Query {
    int op, id, x;
} q[MAXN], ql[MAXN], qr[MAXN];

void dfs1(int u) {
    siz[u] = 1;
    for (auto v : g[u]) {
        if (v == fa[u]) continue;
        fa[v] = u, dep[v] = dep[u] + 1;
        dfs1(v);
        if (siz[v] > siz[son[u]]) son[u] = v;
        siz[u] += siz[v];
    }
}

void dfs2(int u, int top) {
    ::top[u] = top;
    dfn[id[u] = ++tot] = u;
    if (son[u]) dfs2(son[u], top);
    for (auto v : g[u]) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}
int lca(int x, int y) {
    while (top[x] ^ top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}

void modify(int u, int v, int val) {
    int tmp = lca(u, v);
    fwk.add(id[u], val), fwk.add(id[v], val);
    fwk.add(id[tmp], -val);
    if (fa[tmp]) fwk.add(id[fa[tmp]], -val);
}

void solve(int l, int r, int L, int R) {
    if (l == r) {
        for (int i = L; i <= R; i++)
            if (q[i].op == 2) ans[q[i].id] = l;
        return;
    }
    int mid = (l + r) >> 1, cntl = 0, cntr = 0, all = 0;
    for (int i = L; i <= R; i++) {
        if (q[i].op == 2) {
            if (fwk.query(id[q[i].x], id[q[i].x] + siz[q[i].x] - 1) == all)
                ql[++cntl] = q[i];
            else
                qr[++cntr] = q[i];
        } else {
            if (val[q[i].x] <= mid)
                ql[++cntl] = q[i];
            else {
                int tmp = q[i].op ? -1 : 1;
                all += tmp;
                modify(a[q[i].x], b[q[i].x], tmp);
                qr[++cntr] = q[i];
            }
        }
    }
    for (int i = 1; i <= cntr; i++) {
        if (qr[i].op == 2) continue;
        int tmp = qr[i].op ? 1 : -1;
        modify(a[qr[i].x], b[qr[i].x], tmp);
    }
    for (int i = 1; i <= cntl; i++) q[L + i - 1] = ql[i];
    for (int i = 1; i <= cntr; i++) q[L + cntl + i - 1] = qr[i];
    if (cntl) solve(l, mid, L, L + cntl - 1);
    if (cntr) solve(mid + 1, r, L + cntl, R);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].emplace_back(v), g[v].emplace_back(u);
    }
    int mx = 0;
    for (int i = 1; i <= m; i++) {
        cin >> q[i].op;
        q[i].id = i;
        if (!q[i].op) {
            cin >> a[i] >> b[i] >> val[i];
            q[i].x = i;
            mx = max(mx, val[i]);
        } else
            cin >> q[i].x;
    }
    dfs1(1), dfs2(1, 1);
    solve(-1, mx, 1, m);
    for (int i = 1; i <= m; i++)
        if (ans[i]) cout << ans[i] << '\n';
    return 0;
}