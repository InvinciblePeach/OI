#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e5 + 10, MAXV = 1e9;
int n, m, tot, a[MAXN], ans[MAXN * 3];
vector<pii> qry[MAXN];

namespace fenwick {
    int t[MAXN];

    constexpr int lowbit(const int &x) { return x & -x; }

    void init() { memset(t, 0x3f, sizeof(t)); }

    void add(int x, int val) {
        for (; x <= n; x += lowbit(x)) t[x] = min(t[x], val);
    }

    int query(int x) {
        int res = INT_MAX;
        for (; x; x -= lowbit(x)) res = min(res, t[x]);
        return res;
    }
} // namespace fenwick

namespace sgt {
#define lc(p) t[p].lc
#define rc(p) t[p].rc
#define lson lc(p), l, mid
#define rson rc(p), mid + 1, r
    struct Node {
        int lc, rc, mx;
    } t[MAXN << 5];
    int rt, tot;

    void init() {
        for (int i = 1; i <= tot; i++) t[i].lc = t[i].rc = t[i].mx = 0;
    }

    void pushup(int p) { t[p].mx = max(t[lc(p)].mx, t[rc(p)].mx); }

    void modify(int &p, int l, int r, int x, int val) {
        if (!p) p = ++tot;
        if (l == r) return t[p].mx = max(t[p].mx, val), void();
        int mid = (l + r) >> 1;
        if (x <= mid)
            modify(lson, x, val);
        else
            modify(rson, x, val);
        pushup(p);
    }

    int query(int p, int l, int r, int x, int y) {
        if (!p) return 0;
        if (x <= l && r <= y) return t[p].mx;
        int mid = (l + r) >> 1;
        if (y <= mid) return query(lson, x, y);
        if (x > mid) return query(rson, x, y);
        return max(query(lson, x, y), query(rson, x, y));
    }

    void modify(int x, int val) { modify(rt, 0, MAXV, x, val); }
    int query(int x, int y) { return query(rt, 0, MAXV, x, y); }
} // namespace sgt

void solve() {
    sgt::init();
    fenwick::init();
    for (int i = 1; i <= n; i++) {
        int pos = sgt::query(a[i], MAXV);
        while (pos) {
            fenwick::add(n - pos + 1, a[pos] - a[i]);
            pos = sgt::query(a[i], (a[pos] + a[i] - 1) >> 1);
        }
        sgt::modify(a[i], i);
        for (auto [l, id] : qry[i]) ans[id] = min(ans[id], fenwick::query(n - l + 1));
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> m;
    for (int i = 1, l, r; i <= m; i++) {
        cin >> l >> r;
        ans[i] = MAXV, qry[r].emplace_back(l, i);
    }
    solve();
    for (int i = 1; i <= n; i++) a[i] = MAXV - a[i];
    solve();
    for (int i = 1; i <= m; i++) cout << ans[i] << '\n';

    return 0;
}