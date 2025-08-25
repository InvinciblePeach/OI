#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

namespace tjy {
    const int MAXN = 2e5 + 10;

    int n, ans, D, cnt, rt, tot, top, rub[MAXN];

    struct Point {
        int x[2], w;

        Point() {}
        Point(int X, int Y, int W) { x[0] = X, x[1] = Y, w = W; }
        bool operator<(const Point &o) const { return x[D] < o.x[D]; }
    } num[MAXN];

    struct Node {
        int lc, rc, mn[2], mx[2], sum, siz;
        Point nw;
    } t[MAXN];

    int newnode() {
        if (top) return rub[top--];
        return ++tot;
    }

    void pushup(int p) {
        for (int i = 0; i <= 1; i++) {
            t[p].mn[i] = t[p].mx[i] = t[p].nw.x[i];
            if (t[p].lc)
                t[p].mn[i] = min(t[p].mn[i], t[t[p].lc].mn[i]),
                t[p].mx[i] = max(t[p].mx[i], t[t[p].lc].mx[i]);
            if (t[p].rc)
                t[p].mn[i] = min(t[p].mn[i], t[t[p].rc].mn[i]),
                t[p].mx[i] = max(t[p].mx[i], t[t[p].rc].mx[i]);
        }
        t[p].sum = t[t[p].lc].sum + t[t[p].rc].sum + t[p].nw.w;
        t[p].siz = t[t[p].lc].siz + t[t[p].rc].siz + 1;
    }

    int build(int l, int r, int d) {
        if (l > r) return 0;
        int mid = (l + r) >> 1, p = newnode();
        D = d, nth_element(num + l, num + mid, num + r + 1), t[p].nw = num[mid];
        t[p].lc = build(l, mid - 1, d ^ 1), t[p].rc = build(mid + 1, r, d ^ 1);
        return pushup(p), p;
    }

    void down(const int &p, const int &id) {
        if (t[p].lc) down(t[p].lc, id);
        num[t[t[p].lc].siz + id + 1] = t[p].nw, rub[++top] = p;
        if (t[p].rc) down(t[p].rc, t[t[p].lc].siz + id + 1);
    }

    int insert(int p, const Point &tmp, const int &d) {
        if (!p) {
            p = newnode();
            t[p].lc = t[p].rc = 0, t[p].nw = tmp;
            return pushup(p), p;
        }
        if (tmp.x[d] <= t[p].nw.x[d]) t[p].lc = insert(t[p].lc, tmp, d ^ 1);
        else t[p].rc = insert(t[p].rc, tmp, d ^ 1);
        // cerr << p << '\n';
        return pushup(p), p;
    }

    constexpr bool in(int x1, int X1, int x2, int X2, int y1, int Y1, int y2,
                      int Y2) {
        return x1 <= X1 && x2 >= X2 && y1 <= Y1 && y2 >= Y2;
    }

    constexpr bool out(int x1, int X1, int x2, int X2, int y1, int Y1, int y2,
                       int Y2) {
        return x1 > X2 || x2 < X1 || y1 > Y2 || y2 < Y1;
    }

    int query(const int &p, const int &x1, const int &x2, const int &y1,
              const int &y2) {
        if (!p) return 0;
        int res = 0;
        if (in(x1, t[p].mn[0], x2, t[p].mx[0], y1, t[p].mn[1], y2, t[p].mx[1]))
            return t[p].sum;
        if (out(x1, t[p].mn[0], x2, t[p].mx[0], y1, t[p].mn[1], y2, t[p].mx[1]))
            return 0;
        if (in(x1, t[p].nw.x[0], x2, t[p].nw.x[0], y1, t[p].nw.x[1], y2,
               t[p].nw.x[1]))
            res += t[p].nw.w;
        return res + query(t[p].lc, x1, x2, y1, y2) +
               query(t[p].rc, x1, x2, y1, y2);
    }

    signed main() {
        ios::sync_with_stdio(0);
        cin.tie(0), cout.tie(0);

        cin >> n;
        while (true) {
            static int op;
            cin >> op;
            if (op == 3) break;
            if (op == 1) {
                static int x, y, a;
                cin >> x >> y >> a;
                rt = insert(rt, Point(x ^ ans, y ^ ans, a ^ ans), 0);
                // cerr << rt << '\n';
                cnt++;
                if (cnt >= 500) {
                    down(rt, 0);
                    rt = build(1, t[rt].siz, 1);
                    cnt = 0;
                }
            } else if (op == 2) {
                static int x1, x2, y1, y2;
                cin >> x1 >> y1 >> x2 >> y2;
                x1 ^= ans, y1 ^= ans, x2 ^= ans, y2 ^= ans;
                cout << (ans = query(rt, x1, x2, y1, y2)) << '\n';
            }
        }

        return 0;
    }
}

signed main() {
    return tjy::main();
}