#include <bits/stdc++.h>
#define lc(p) p << 1
#define rc(p) p << 1 | 1

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 1e4 + 10, INF = 0x3f3f3f3f;
int T, n, k, q, a[11];

struct Node {
    int l, r;
    int mx, add;
} t[MAXN << 2][11];

void pushup(int p, int lv) { t[p][lv].mx = max(t[lc(p)][lv].mx, t[rc(p)][lv].mx); }

void pushdown(int p, int lv) {
    int &add = t[p][lv].add;
    t[lc(p)][lv].mx += add, t[rc(p)][lv].mx += add;
    t[lc(p)][lv].add += add, t[rc(p)][lv].add += add;
    add = 0;
}

void build(int p, int lv, int l, int r) {
    t[p][lv].l = l, t[p][lv].r = r, t[p][lv].add = 0;
    if (l == r) {
        t[p][lv].mx = (lv != 1 ? -INF : 0);
        return;
    }
    int mid = (l + r) >> 1;
    build(lc(p), lv, l, mid), build(rc(p), lv, mid + 1, r);
    pushup(p, lv);
}

void add(int p, int lv, int l, int r, int val) {
    if (l <= t[p][lv].l && t[p][lv].r <= r) {
        t[p][lv].mx += val, t[p][lv].add += val;
        return;
    }
    pushdown(p, lv);
    if (l <= t[lc(p)][lv].r) add(lc(p), lv, l, r, val);
    if (r >= t[rc(p)][lv].l) add(rc(p), lv, l, r, val);
    pushup(p, lv);
}

void modify(int p, int lv, int pos, int val) {
    if (t[p][lv].l == t[p][lv].r) return t[p][lv].mx = val, void();
    pushdown(p, lv);
    if (pos <= t[lc(p)][lv].r)
        modify(lc(p), lv, pos, val);
    else
        modify(rc(p), lv, pos, val);
    pushup(p, lv);
}

void search(int p, int lv, int l, int r) {
    if (t[p][lv].l == t[p][lv].r) {
        int nxt = upper_bound(a + 1, a + 1 + k, t[p][lv].mx) - a - 1;
        modify(1, nxt, t[p][lv].l, t[p][lv].mx);
        t[p][lv].mx = -INF;
        return;
    }
    pushdown(p, lv);
    if (l <= t[lc(p)][lv].r && t[lc(p)][lv].mx >= a[lv + 1]) search(lc(p), lv, l, r);
    if (r >= t[rc(p)][lv].l && t[rc(p)][lv].mx >= a[lv + 1]) search(rc(p), lv, l, r);
    pushup(p, lv);
}

int query(int p, int lv, int l, int r) {
    if (l <= t[p][lv].l && t[p][lv].r <= r) return t[p][lv].mx;
    pushdown(p, lv);
    int res = -INF;
    if (l <= t[lc(p)][lv].r) res = max(res, query(lc(p), lv, l, r));
    if (r >= t[rc(p)][lv].l) res = max(res, query(rc(p), lv, l, r));
    pushup(p, lv);
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    for (int _ = 1; _ <= T; _++) {
        cout << "Case " << _ << ":\n";

        cin >> n >> k >> q;
        build(1, 1, 1, n);
        for (int i = 2; i <= k; i++) {
            cin >> a[i];
            build(1, i, 1, n);
        }
        a[k + 1] = INF;
        while (q-- > 0) {
            static char op;
            static int l, r, x;
            cin >> op >> l >> r;
            if (op == 'W') {
                cin >> x;
                for (int i = 1; i <= k; i++)
                    if (t[1][i].mx >= 0) add(1, i, l, r, x * i);
                for (int i = 1; i <= k; i++)
                    if (t[1][i].mx >= 0) search(1, i, l, r);
            } else {
                for (int i = k, res; i; i--) {
                    if (t[1][i].mx >= 0 && (res = query(1, i, l, r)) >= 0) {
                        cout << res << '\n';
                        break;
                    }
                }
            }
        }
    }

    return 0;
}