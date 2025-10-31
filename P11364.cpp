#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 5e5 + 10;
int n, q;
vector<int> g[MAXN];

namespace pou {
    int tot, dep[MAXN], top[MAXN], fa[MAXN], son[MAXN], siz[MAXN], dfn[MAXN], id[MAXN];
    void dfs1(int u, int fa) {
        pou::fa[u] = fa;
        siz[u] = 1;
        for (auto v : g[u]) {
            if (v == fa) continue;
            dep[v] = dep[u] + 1;
            dfs1(v, u);
            if (siz[v] > siz[son[u]]) son[u] = v;
            siz[u] += siz[v];
        }
    }

    void dfs2(int u, int fa, int top) {
        dfn[id[u] = ++tot] = u;
        pou::top[u] = top;
        if (son[u]) dfs2(son[u], u, top);
        for (auto v : g[u]) {
            if (v == fa || v == son[u]) continue;
            dfs2(v, u, v);
        }
    }

    void main() {
        dep[1] = 1;
        dfs1(1, 1);
        dfs2(1, 1, 1);
    }

    int lca(int u, int v) {
        while (top[u] ^ top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
} // namespace pou
using pou::lca;

struct L {
    int l, r, w;
} a[MAXN << 1];
int cnt;

struct Query {
    int l, r, k, id;
} qry[MAXN];

namespace prework {
    int w[MAXN], l[MAXN], r[MAXN], st[MAXN], top;
    void main() {
        for (int i = 1; i < n; i++) w[i] = pou::dep[lca(i, i + 1)];
        for (int i = 1; i < n; i++) {
            while (top && w[st[top]] > w[i]) r[st[top--]] = i - 1;
            l[i] = st[top] + 1;
            st[++top] = i;
        }
        while (top) r[st[top--]] = n - 1;
        for (int i = 1; i <= n; i++) a[++cnt] = {i, i, pou::dep[i]};
        for (int i = 1; i < n; i++) a[++cnt] = {l[i], r[i] + 1, w[i]};
    }
} // namespace prework

struct SGT {
#define lc(p) p << 1
#define rc(p) p << 1 | 1
#define lson lc(p), l, mid
#define rson rc(p), mid + 1, r
    int t[MAXN << 2];

    void pushup(int p) { t[p] = max(t[lc(p)], t[rc(p)]); }

    void build(int p, int l, int r) {
        t[p] = 0;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(lson), build(rson);
    }

    void modify(int p, int l, int r, int pos, int val) {
        if (l == r) return t[p] = max(t[p], val), void();
        int mid = (l + r) >> 1;
        pos <= mid ? modify(lson, pos, val) : modify(rson, pos, val);
        pushup(p);
    }

    int query(int p, int l, int r, int x, int y) {
        if (x <= l && r <= y) return t[p];
        int mid = (l + r) >> 1;
        if (y <= mid) return query(lson, x, y);
        if (x > mid) return query(rson, x, y);
        return max(query(lson, x, y), query(rson, x, y));
    }
} T;

int ans[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    pou::main(), prework::main();
    cin >> q;
    for (int i = 1; i <= q; i++) cin >> qry[i].l >> qry[i].r >> qry[i].k, qry[i].id = i;
    sort(qry + 1, qry + 1 + q, [](Query a, Query b) { return a.r > b.r; });
    sort(a + 1, a + 1 + cnt, [](L a, L b) { return a.r > b.r; });
    for (int i = 1, j = 1; i <= q; i++) {
        auto [l, r, k, id] = qry[i];
        for (; j <= cnt && a[j].r >= r; j++) T.modify(1, 1, n, a[j].l, a[j].w);
        ans[id] = max(ans[id], T.query(1, 1, n, 1, r - k + 1));
    }
    T.build(1, 1, n);
    sort(qry + 1, qry + 1 + q, [](Query a, Query b) { return a.k > b.k; });
    sort(a + 1, a + 1 + cnt, [](L a, L b) { return a.r - a.l + 1 > b.r - b.l + 1; });
    for (int i = 1, j = 1; i <= q; i++) {
        auto [l, r, k, id] = qry[i];
        for (; j <= cnt && a[j].r - a[j].l + 1 >= k; j++) T.modify(1, 1, n, a[j].r, a[j].w);
        ans[id] = max(ans[id], T.query(1, 1, n, l + k - 1, r));
    }
    for (int i = 1; i <= q; i++) cout << ans[i] << '\n';

    return 0;
}