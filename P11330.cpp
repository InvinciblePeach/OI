#include <bits/stdc++.h>
#define lc(p) p << 1
#define rc(p) p << 1 | 1
#define lson lc(p), l, mid
#define rson rc(p), mid + 1, r
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e5 + 10, INF = 0x3f3f3f3f3f3f3f3f;
int n, q, dep[MAXN], cnt;
bitset<MAXN> vis;
vector<pii> g[MAXN];

namespace bit {
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
} // namespace bit

struct SGT {
    struct Node {
        int mn, tag;
        Node() { mn = INF; }

        constexpr void entag(const int &val) { mn += val, tag += val; }
    } t[MAXN << 2];

    void pushup(int p) { t[p].mn = min(t[lc(p)].mn, t[rc(p)].mn); }

    void pushdown(int p) {
        auto &tag = t[p].tag;
        if (tag) {
            t[lc(p)].entag(tag);
            t[rc(p)].entag(tag);
            tag = 0;
        }
    }

    void modify(int p, int l, int r, int x, int y, int val) {
        if (x <= l && r <= y) return t[p].entag(val);
        pushdown(p);
        int mid = (l + r) >> 1;
        if (x <= mid) modify(lson, x, y, val);
        if (y > mid) modify(rson, x, y, val);
        pushup(p);
    }

    void update(int p, int l, int r, int x, int val) {
        if (l == r) return void(t[p].mn = val);
        pushdown(p);
        int mid = (l + r) >> 1;
        if (x <= mid) update(lson, x, val);
        if (x > mid) update(rson, x, val);
        pushup(p);
    }

    int query(int p, int l, int r, int x, int y) {
        if (x <= l && r <= y) return t[p].mn;
        pushdown(p);
        int mid = (l + r) >> 1;
        if (y <= mid) return query(lson, x, y);
        if (x > mid) return query(rson, x, y);
        return min(query(lson, x, y), query(rson, x, y));
    }
} T1, T2;

namespace chain {
    int dfn[MAXN], id[MAXN], fa[MAXN], siz[MAXN], top[MAXN], son[MAXN], up[MAXN];
    int tot;

    void dfs1(int u, int fa) {
        chain::fa[u] = fa;
        siz[u] = 1;
        for (auto [v, w] : g[u]) {
            if (v == fa) continue;
            dep[v] = dep[u] + w, up[v] = w;
            dfs1(v, u);
            if (siz[v] > siz[son[u]]) son[u] = v;
            siz[u] += siz[v];
        }
    }

    void dfs2(int u, int fa, int top) {
        dfn[id[u] = ++tot] = u;
        chain::top[u] = top;
        if (son[u]) dfs2(son[u], u, top);
        for (auto [v, w] : g[u]) {
            if (v == fa || v == son[u]) continue;
            dfs2(v, u, v);
        }
    }

    int calc(int u) { return dep[u] + bit::query(id[u]); }

    int get(int u, int z) {
        if (vis[u]) return -calc(u);
        if (z) {
            return siz[son[u]] + 1 < siz[u]
                       ? T1.query(1, 1, n, id[u] + siz[son[u]] + 1, id[u] + siz[u] - 1) - (calc(u) << 1)
                       : INF;
        } else
            return T1.query(1, 1, n, id[u], id[u] + siz[u] - 1) - (calc(u) << 1);
    }

    int query(int u) {
        if (!cnt) return -1;
        int res = INF;
        int tmp = u;
        while (u) {
            res = min(res, get(u, 0));
            res = min(res, T2.query(1, 1, n, id[top[u]], id[u]));
            u = fa[top[u]];
        }
        return res + calc(tmp);
    }
    void update(int u) {
        while (u) {
            T2.update(1, 1, n, id[u], get(u, 1));
            u = fa[top[u]];
        }
    }

    void init() { dfs1(1, 0), dfs2(1, 0, 1); }

} // namespace chain
using chain::id, chain::siz, chain::up, chain::calc, chain::query, chain::update;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> q;
    for (int i = 1, u, v, w; i < n; i++) {
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    chain::init();
    while (q-- > 0) {
        static int op, u, v, w;
        cin >> op >> u;
        if (op == 1) cout << query(u) << "\n";
        if (op == 2) {
            if (vis[u])
                cnt--, T1.update(1, 1, n, id[u], INF);
            else
                cnt++, T1.update(1, 1, n, id[u], calc(u));
            vis[u] = vis[u] ^ 1;
            update(u);
        }
        if (op == 3) {
            cin >> v >> w;
            if (id[u] > id[v]) swap(u, v);
            T1.modify(1, 1, n, id[v], id[v] + siz[v] - 1, w - up[v]);
            T2.modify(1, 1, n, id[v], id[v] + siz[v] - 1, up[v] - w);
            bit::add(id[v], id[v] + siz[v] - 1, w - up[v]);
            up[v] = w;
            update(u);
        }
    }

    return 0;
}