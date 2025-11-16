#include <bits/stdc++.h>
#define lc(p) p << 1
#define rc(p) p << 1 | 1
#define lson lc(p), l, mid
#define rson rc(p), mid + 1, r

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 5e5 + 10;
struct Node {
    int l, r, mn, mx, sum, tag;

    void entag(int val) {
        sum = val * (r - l + 1);
        mn = mx = tag = val;
    }
} t[MAXN << 2];
int n, q, a[MAXN];

void pushup(int p) {
    t[p].mx = max(t[lc(p)].mx, t[rc(p)].mx);
    t[p].mn = min(t[lc(p)].mn, t[rc(p)].mn);
    t[p].sum = t[lc(p)].sum + t[rc(p)].sum;
}

void pushdown(int p) {
    auto &tag = t[p].tag;
    if (~tag) {
        t[lc(p)].entag(tag);
        t[rc(p)].entag(tag);
        tag = -1;
    }
}

void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r, t[p].tag = -1;
    if (l == r) return t[p].entag(a[l]);
    int mid = (l + r) >> 1;
    build(lson), build(rson);
    pushup(p);
}

void modify(int p, int l, int r, int val) {
    if (l <= t[p].l && t[p].r <= r && t[p].mn == t[p].mx) return t[p].entag(t[p].mx / val);
    pushdown(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if (l <= mid) modify(lc(p), l, r, val);
    if (r > mid) modify(rc(p), l, r, val);
    pushup(p);
}

void assign(int p, int l, int r, int val) {
    if (l <= t[p].l && t[p].r <= r) return t[p].entag(val);
    pushdown(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if (l <= mid) assign(lc(p), l, r, val);
    if (r > mid) assign(rc(p), l, r, val);
    pushup(p);
}

int query(int p, int l, int r) {
    if (l <= t[p].l && t[p].r <= r) return t[p].sum;
    pushdown(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if (r <= mid) return query(lc(p), l, r);
    if (l > mid) return query(rc(p), l, r);
    return query(lc(p), l, r) + query(rc(p), l, r);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
    while (q-- > 0) {
        static int op, l, r, x;
        cin >> op >> l >> r;
        if (op == 1) cin >> x, modify(1, l, r, x);
        if (op == 2) cin >> x, assign(1, l, r, x);
        if (op == 3) cout << query(1, l, r) << '\n';
    }

    return 0;
}