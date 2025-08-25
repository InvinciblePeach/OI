#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 8e4 + 10;
int T, n, m, q, fa[MAXN][20], siz[MAXN], dep[MAXN], rt[MAXN];
int a[MAXN], b[MAXN], cnt, ans;
bitset<MAXN> vis;
vector<int> g[MAXN];

struct HJT {
    struct Node {
        int l, r, sum, lc, rc;
    } t[MAXN << 9];
    int tot;

    void pushup(int p) { t[p].sum = t[t[p].lc].sum + t[t[p].rc].sum; }

    int build(int l, int r) {
        int p = ++tot;
        t[p].l = l, t[p].r = r;
        if (l == r) return p;

        int mid = (l + r) >> 1;
        t[p].lc = build(l, mid), t[p].rc = build(mid + 1, r);
        return pushup(p), p;
    }

    int modify(int pre, int x) {
        int p = ++tot;
        t[p] = t[pre];
        if (t[p].l == t[p].r) return t[p].sum++, p;
        if (x <= t[t[p].lc].r) t[p].lc = modify(t[pre].lc, x);
        else t[p].rc = modify(t[pre].rc, x);
        return pushup(p), p;
    }

    int query(int x, int y, int pre1, int pre2, int k) {
        if (t[x].l == t[x].r) return b[t[x].l];
        int lsize = t[t[x].lc].sum + t[t[y].lc].sum - t[t[pre1].lc].sum - t[t[pre2].lc].sum;
        if (k <= lsize) return query(t[x].lc, t[y].lc, t[pre1].lc, t[pre2].lc, k);
        else return query(t[x].rc, t[y].rc, t[pre1].rc, t[pre2].rc, k - lsize);
    }
} sgt;

struct DSU {
    int fa[MAXN];

    void init() { for (int i = 1; i <= n; i++) fa[i] = i; }

    int get(int x) {
        if (fa[x] == x) return x;
        return fa[x] = get(fa[x]);
    }

    void merge(int x, int y) { fa[get(x)] = get(y); }
} dsu;

int lca(int x, int y) {
    if (dep[x] > dep[y]) swap(x, y);
    for (int k = 16; ~k; k--)
        if (dep[fa[y][k]] >= dep[x]) y = fa[y][k];

    if (x == y) return x;
    for (int k = 16; ~k; k--)
        if (fa[x][k] ^ fa[y][k]) x = fa[x][k], y = fa[y][k];
    return fa[x][0];
}

void dfs(int u, int f, int root) {
    vis[u] = 1, dsu.fa[u] = fa[u][0] = f, siz[root]++, dep[u] = dep[f] + 1;
    for (int i = 1; i <= 16; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    rt[u] = sgt.modify(rt[f], lower_bound(b + 1, b + cnt + 1, a[u]) - b);
    for (auto v : g[u]) {
        if (v == f) continue;
        dfs(v, u, root);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++)
        cin >> a[i], b[i] = a[i];
    sort(b + 1, b + 1 + n);
    cnt = unique(b + 1, b + 1 + n) - b - 1;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    rt[0] = sgt.build(1, cnt);
    dsu.init();
    for (int i = 1; i <= n; i++)
        if (!vis[i]) dfs(i, 0, i), dsu.fa[i] = i;
    while (q --> 0) {
        static char c;
        static int x, y, k;
        cin >> c >> x >> y;
        x ^= ans, y ^= ans;
        if (c == 'Q') {
            cin >> k, k ^= ans;
            int tmp = lca(x, y);
            cout << (ans = sgt.query(rt[x], rt[y], rt[tmp], rt[fa[tmp][0]], k)) << '\n';
        } else {
            g[x].emplace_back(y);
            g[y].emplace_back(x);
            int u = dsu.get(x), v = dsu.get(y);
            if (siz[u] < siz[v]) swap(u, v), swap(x, y);
            dsu.fa[y] = x;
            dfs(y, x, u);
        }
    }

    return 0;
}