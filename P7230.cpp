#include <bits/stdc++.h>
#define lc(p) ((p) << 1)
#define rc(p) ((p) << 1 | 1)

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 1e5 + 10, INF = 0x3f3f3f3f;
int n, k, m, a[MAXN], f[MAXN], ans[MAXN];
vector<int> g[MAXN];
bitset<MAXN> vis;
multiset<int> st[MAXN];

namespace stk {
    struct Node {
        int p, x, y, z;
    } st[MAXN * 400];
    int tp = 0;

    void insert(int p, int x, int y, int z) { st[++tp] = {p, x, y, z}; }
    Node top() { return st[tp]; }
    Node pop() { return st[tp--]; }
} // namespace stk

namespace sgt {
    struct Node {
        int l, r, res, mn, tag;

        void entag(int p, int k) {
            stk::insert(p, res, mn, tag);
            res = k, mn = k - r + 1, tag = k;
        }
    } t[MAXN << 2];

    void pushup(int p) {
        stk::insert(p, t[p].res, t[p].mn, t[p].tag);
        t[p].mn = min(t[lc(p)].mn, t[rc(p)].mn);
        t[p].res = max(t[lc(p)].res, t[rc(p)].res);
    }

    void pushdown(int p) {
        auto &tag = t[p].tag;
        if (tag) {
            t[lc(p)].entag(lc(p), tag);
            t[rc(p)].entag(rc(p), tag);
            stk::insert(p, t[p].res, t[p].mn, t[p].tag);
            tag = 0;
        }
    }

    void build(int p, int l, int r) {
        t[p].l = l, t[p].r = r;
        if (l == r) return t[p].entag(p, f[l]);
        int mid = (l + r) >> 1;
        build(lc(p), l, mid), build(rc(p), mid + 1, r);
        pushup(p);
    }

    void modify(int p, int l, int r, int val) {
        if (l <= t[p].l && t[p].r <= r) return t[p].entag(p, val);
        pushdown(p);
        if (l <= t[lc(p)].r) modify(lc(p), l, r, val);
        if (r >= t[rc(p)].l) modify(rc(p), l, r, val);
        pushup(p);
    }

    int query(int p, int x) {
        if (t[p].l == t[p].r) return t[p].res;
        pushdown(p);
        if (x <= t[lc(p)].r) return query(lc(p), x);
        return query(rc(p), x);
    }

    int find(int p, int val) {
        if (t[p].l == t[p].r) return t[p].res < val ? n + 1 : t[p].l;
        pushdown(p);
        if (t[lc(p)].res < val) return find(rc(p), val);
        return find(lc(p), val);
    }

    void update(int l, int r, int val) {
        l = max(1, l), r = min(r, find(1, val) - 1);
        if (l > r) return;
        modify(1, l, r, val);
    }
} // namespace sgt

namespace solve {
    struct Node {
        int l, r;
        vector<pii> sg;
    } t[MAXN << 2];

    void rollback(int p, int tmp) {
        while (stk::tp > tmp) {
            auto [p, x, y, z] = stk::pop();
            sgt::t[p].res = x, sgt::t[p].mn = y, sgt::t[p].tag = z;
        }
        for (auto [x, val] : t[p].sg) st[val].emplace(x);
    }

    void build(int p, int l, int r) {
        t[p].l = l, t[p].r = r;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(lc(p), l, mid), build(rc(p), mid + 1, r);
    }

    void modify(int p, int l, int r, int x, int val) {
        if (l <= t[p].l && t[p].r <= r) return t[p].sg.emplace_back(x, val), void();
        if (l <= t[lc(p)].r) modify(lc(p), l, r, x, val);
        if (r >= t[rc(p)].l) modify(rc(p), l, r, x, val);
    }

    void dfs(int p) {
        int tmp = stk::tp;
        for (auto [x, val] : t[p].sg) {
            auto &s = st[val];
            s.erase(s.find(x));
            if (s.find(x) != s.end()) continue;
            auto it = s.lower_bound(x);
            int l = *prev(it), r = *it;
            sgt::update(l + 1, x, r);
        }
        if (t[p].l == t[p].r) {
            if (vis[t[p].l]) cout << (sgt::t[1].mn <= n ? sgt::t[1].mn : -1) << '\n';
            return rollback(p, tmp);
        }
        dfs(lc(p)), dfs(rc(p));
        return rollback(p, tmp);
    }

    void solve() {
        cin >> n >> k >> m;
        for (int i = 1; i <= k; i++) st[i].emplace(-INF), st[i].emplace(INF);
        for (int i = 1; i <= n; i++) cin >> a[i], st[a[i]].emplace(i), g[i].emplace_back(a[i]);
        build(1, 1, m);
        for (int i = 1; i <= m; i++) {
            static int op, p, v;
            cin >> op;
            if (op == 1) {
                cin >> p >> v;
                st[v].emplace(p);
                g[p].emplace_back(v);
                if (1 <= i - 1) modify(1, 1, i - 1, p, v);
                if (i <= m) modify(1, i, m, p, a[p]);
                a[p] = v;
            } else {
                vis[i] = 1;
            }
        }
        for (int i = 1; i <= k; i++) f[1] = max(f[1], *st[i].lower_bound(1));
        for (int i = 2; i <= n; i++) {
            f[i] = f[i - 1];
            for (auto j : g[i - 1]) f[i] = max(f[i], *st[j].lower_bound(i));
        }

        sgt::build(1, 1, n);
        dfs(1);
    }
} // namespace solve

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    solve::solve();

    return 0;
}