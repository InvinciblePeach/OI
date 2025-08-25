#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10, INF = 0x3f3f3f3f;
int n, m, a[MAXN], b[MAXN];

constexpr int lc(int p) { return p << 1; }
constexpr int rc(int p) { return p << 1 | 1; }

struct Node {
    int l, r;
    int x, y, p, q, ans;

    Node() { y = INF, x = p = q = ans = -INF; }
} t[MAXN << 2];

Node merge(const Node &a, const Node &b) {
    Node res;
    res.l = a.l, res.r = b.r;
    res.x = max(a.x, b.x);
    res.y = min(a.y, b.y);
    res.p = max({a.p,b.p, a.x - b.y});
    res.q = max({a.q,b.q, b.x - a.y});
    res.ans = max({a.ans, b.ans, a.p + b.x, a.x + b.q});
    return res;
}

void pushup(int p) { t[p] = merge(t[lc(p)], t[rc(p)]); }

void build(int p, int l, int r) {
    t[p].l = r, t[p].r = r;
    if (l == r) {
        t[p].x = a[l], t[p].y = b[r];
        t[p].p = t[p].q = t[p].ans = -INF;
        return;
    }

    int mid = (l + r) >> 1;
    build(lc(p), l, mid), build(rc(p), mid + 1, r);
    return pushup(p);
}

void modifya(int p, int x, int y) {
    if (t[p].l == t[p].r) {
        t[p].x = y;
        t[p].p = t[p].q = t[p].ans = -INF;
        return;
    }

    if (x <= t[lc(p)].r) modifya(lc(p), x, y);
    else modifya(rc(p), x, y);
    return pushup(p);
}

void modifyb(int p, int x, int y) {
    if (t[p].l == t[p].r) {
        t[p].y = y;
        t[p].p = t[p].q = t[p].ans = -INF;
        return;
    }

    if (x <= t[lc(p)].r) modifyb(lc(p), x, y);
    else modifyb(rc(p), x, y);
    return pushup(p);
}

Node query(int p, int l, int r) {
    if (l <= t[p].l && t[p].r <= r) return t[p];

    Node res;
    res.l = t[p].l, res.r = t[p].r;
    if (l <= t[lc(p)].r) res = merge(query(lc(p), l, r), res);
    if (r >= t[rc(p)].l) res = merge(res, query(rc(p), l, r));
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    build(1, 1, n);

    while (m --> 0) {
        static int opt, x, y;
        cin >> opt >> x >> y;
        if (opt == 1) modifya(1, x, y);
        if (opt == 2) modifyb(1, x, y);
        if (opt == 3) cout << query(1, x, y).ans << '\n';
    }

    return 0;
}