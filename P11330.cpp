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
int n, q, dep[MAXN];
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

    void modify(int p, int l, int r, int x, int val) {
        if (l == r) return void(t[p].mn = val);
        pushdown(p);
        int mid = (l + r) >> 1;
        if (x <= mid) modify(lson, x, val);
        if (x > mid) modify(rson, x, val);
        pushup(p);
    }

    int query(int p, int l, int r, int x, int y) {
        if (x <= l && r <= y) return t[p].mn;
        pushdown(p);
        int mid = (l + r) >> 1;
        if (r <= mid) return query(lson, x, y);
        if (l > mid) return query(rson, x, y);
        return min(query(lson, x, y), query(rson, x, y));
    }
} T1, T2;

namespace chain {
    int dfn[MAXN], id[MAXN], fa[MAXN], siz[MAXN], top[MAXN], son[MAXN];
    int tot;

    void dfs1(int u, int fa) {
        chain::fa[u] = fa;
        siz[u] = 1;
        for (auto [v, w] : g[u]) {
            if (v == fa) continue;
            dep[v] = dep[u] + w;
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

} // namespace chain

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    /* code */

    return 0;
}