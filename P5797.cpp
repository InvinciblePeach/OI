#include <bits/stdc++.h>
#define lc(p) p << 1
#define rc(p) p << 1 | 1
#define lson lc(p), l, mid
#define rson rc(p), mid + 1, r

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 2e5 + 10;
int n, m, a[MAXN << 1], nw;
vector<int> pos[MAXN];

namespace sgt {
    struct Node {
        int l, r, ld, rd, res;
    } t[MAXN << 3];

    Node merge(Node l, Node r) {
        Node res = {l.l, r.r, l.ld, r.rd, l.res + r.res};
        bool flag = ll(a[l.r] - nw) * (a[r.l] - nw) < 0;
        if (flag) {
            if (l.ld == l.r - l.l + 1) res.ld += r.ld;
            if (r.rd == r.r - r.l + 1) res.rd += l.rd;
            res.res += ((l.rd + r.ld) >> 1) - (l.rd >> 1) - (r.ld >> 1);
        }
        return res;
    }

    void pushup(int p) { t[p] = merge(t[lc(p)], t[rc(p)]); }

    void build(int p, int l, int r) {
        t[p].l = l, t[p].r = r;
        if (l == r) {
            if (nw == a[l])
                t[p] = {l, r, 0, 0, 0};
            else
                t[p] = {l, r, 1, 1, 0};
            return;
        }
        int mid = (l + r) >> 1;
        build(lson), build(rson);
        pushup(p);
    }

    void modify(int p, int l, int r, int x) {
        if (l == r) {
            if (nw == a[l])
                t[p].ld = t[p].rd = 0;
            else
                t[p].ld = t[p].rd = 1;
            return;
        }
        int mid = (l + r) >> 1;
        x <= mid ? modify(lson, x) : modify(rson, x);
        pushup(p);
    }

    Node query(int p, int l, int r, int x, int y) {
        if (x <= l && r <= y) return t[p];
        int mid = (l + r) >> 1;
        if (y <= mid) return query(lson, x, y);
        if (x > mid) return query(rson, x, y);
        return merge(query(lson, x, y), query(rson, x, y));
    }

    void modify(int x) { modify(1, 1, n << 1, x); }
    Node query(int x, int y) { return query(1, 1, n << 1, x, y); }
} // namespace sgt

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i], a[i + n] = a[i], pos[a[i]].emplace_back(i);
    sgt::build(1, 1, n << 1);
    for (nw = 1; nw <= m; nw++) {
        for (auto i : pos[nw]) sgt::modify(i), sgt::modify(i + n);
        for (auto i : pos[nw - 1]) sgt::modify(i), sgt::modify(i + n);
        int res = -1;
        if (!pos[nw].empty()) res = n - pos[nw].size() + sgt::query(pos[nw][0], pos[nw][0] + n).res;
        cout << res << " \n"[nw == m];
    }

    return 0;
}