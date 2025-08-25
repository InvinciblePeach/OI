#include <bits/stdc++.h>
#define lc(p) p << 1
#define rc(p) p << 1 | 1

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;
int T, n, q, a[MAXN];

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

struct Node {
    int l, r;
    int val, mx, tag;
} t[MAXN << 2];

void pushup(int p) {
    t[p].mx = max(t[lc(p)].mx, t[rc(p)].mx), t[p].val = (t[lc(p)].val == t[rc(p)].val ? t[lc(p)].val : -1);
}

void pushdown(int p) {
    if (t[p].tag) {
        t[lc(p)].mx = t[lc(p)].val = t[lc(p)].tag = t[p].tag;
        t[rc(p)].mx = t[rc(p)].val = t[rc(p)].tag = t[p].tag;
        t[p].tag = 0;
    }
}

void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r, t[p].tag = 0;
    if (l == r) return t[p].val = t[p].mx = a[l], void();
    int mid = (l + r) >> 1;
    build(lc(p), l, mid), build(rc(p), mid + 1, r);
    pushup(p);
}

void assign(int p, int l, int r, int val) {
    if (l <= t[p].l && t[p].r <= r) return t[p].val = t[p].mx = t[p].tag = val, void();

    pushdown(p);
    if (l <= t[lc(p)].r) assign(lc(p), l, r, val);
    if (r >= t[rc(p)].l) assign(rc(p), l, r, val);
    pushup(p);
}

void modify(int p, int l, int r, int val) {
    if (t[p].mx <= val) return;
    if (l <= t[p].l && t[p].r <= r && t[p].val != -1) return t[p].mx = t[p].val = t[p].tag = gcd(t[p].val, val), void();

    pushdown(p);
    if (l <= t[lc(p)].r) modify(lc(p), l, r, val);
    if (r >= t[rc(p)].l) modify(rc(p), l, r, val);
    pushup(p);
}

int query(int p, int pos) {
    if (t[p].l == t[p].r) return t[p].val;
    pushdown(p);
    if (pos <= t[lc(p)].r) return query(lc(p), pos);
    if (pos >= t[rc(p)].l) return query(rc(p), pos);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        build(1, 1, n);
        cin >> q;
        while (q-- > 0) {
            static int op, l, r, x;
            cin >> op >> l >> r >> x;
            if (op == 1) assign(1, l, r, x);
            else if (op == 2) modify(1, l, r, x);
        }
        for (int i = 1; i <= n; i++) cout << query(1, i) << " \n"[i == n];
    }

    return 0;
}