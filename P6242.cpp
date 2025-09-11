#include <bits/stdc++.h>
#define int long long
#define lc(p) (p) << 1
#define rc(p) (p) << 1 | 1

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 5e5 + 10, INF = 2e9;
int n, m, a[MAXN];

struct Node {
    int l, r;
    int sum, mx, se, cnt, mxh;
    int add, tag, addh, tagh;

    Node() { l = r = sum = mx = se = cnt = mxh = add = tag = addh = tagh = 0; }

    void entag(int v1, int v2, int v3, int v4) {
        sum += v1 * cnt + v2 * (r - l + 1 - cnt);
        mxh = max(mxh, mx + v3);
        mx += v1;
        if (se != -INF) se += v2;
        addh = max(addh, add + v3);
        tagh = max(tagh, tag + v4);
        add += v1, tag += v2;
    }
} t[MAXN << 2];

Node merge(Node a, Node b) {
    Node res;
    res.l = a.l, res.r = b.r;
    res.sum = a.sum + b.sum;
    res.mx = max(a.mx, b.mx);
    res.mxh = max(a.mxh, b.mxh);
    if (a.mx == b.mx) {
        res.se = max(a.se, b.se);
        res.cnt = a.cnt + b.cnt;
    } else if (a.mx == res.mx) {
        res.se = max(a.se, b.mx);
        res.cnt = a.cnt;
    } else {
        res.se = max(a.mx, b.se);
        res.cnt = b.cnt;
    }
    return res;
}

void pushup(int p) { t[p] = merge(t[lc(p)], t[rc(p)]); }

void pushdown(int p) {
    auto &[l, r, sum, mx, se, cnt, mxh, add, tag, addh, tagh] = t[p];
    auto tmp = max(t[lc(p)].mx, t[rc(p)].mx);
    if (t[lc(p)].mx == tmp)
        t[lc(p)].entag(add, tag, addh, tagh);
    else
        t[lc(p)].entag(tag, tag, tagh, tagh);
    if (t[rc(p)].mx == tmp)
        t[rc(p)].entag(add, tag, addh, tagh);
    else
        t[rc(p)].entag(tag, tag, tagh, tagh);
    add = tag = addh = tagh = 0;
}

void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    if (l == r) return t[p].sum = t[p].mx = t[p].mxh = a[l], t[p].se = -INF, t[p].cnt = 1, void();
    int mid = (l + r) >> 1;
    build(lc(p), l, mid), build(rc(p), mid + 1, r);
    pushup(p);
}

void modifyadd(int p, int l, int r, int val) {
    if (l <= t[p].l && t[p].r <= r) return t[p].entag(val, val, val, val);
    pushdown(p);
    if (l <= t[lc(p)].r) modifyadd(lc(p), l, r, val);
    if (r >= t[rc(p)].l) modifyadd(rc(p), l, r, val);
    pushup(p);
}

void modifymin(int p, int l, int r, int val) {
    if (t[p].mx <= val) return;
    if (l <= t[p].l && t[p].r <= r && t[p].se < val) {
        auto tmp = val - t[p].mx;
        t[p].entag(tmp, 0, tmp, 0);
        return;
    }
    pushdown(p);
    if (l <= t[lc(p)].r) modifymin(lc(p), l, r, val);
    if (r >= t[rc(p)].l) modifymin(rc(p), l, r, val);
    pushup(p);
}

Node query(int p, int l, int r) {
    if (l <= t[p].l && t[p].r <= r) return t[p];
    pushdown(p);
    if (l <= t[lc(p)].r && t[rc(p)].l <= r) return merge(query(lc(p), l, r), query(rc(p), l, r));
    if (l <= t[lc(p)].r) return query(lc(p), l, r);
    return query(rc(p), l, r);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
    while (m-- > 0) {
        static int op, l, r, val;
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> val;
            modifyadd(1, l, r, val);
        } else if (op == 2) {
            cin >> val;
            modifymin(1, l, r, val);
        } else if (op == 3) {
            cout << query(1, l, r).sum << '\n';
        } else if (op == 4) {
            cout << query(1, l, r).mx << '\n';
        } else if (op == 5) {
            cout << query(1, l, r).mxh << '\n';
        }
    }

    return 0;
}