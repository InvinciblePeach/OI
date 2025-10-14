#include <bits/stdc++.h>
#define int long long
#define lc(p) p << 1
#define rc(p) p << 1 | 1
#define lson lc(p), l, mid
#define rson rc(p), mid + 1, r

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 5e5 + 10, INF = 0x3f3f3f3f3f3f3f3f;
int n, q;

struct sgt {
    int t[MAXN << 2];

    void pushup(int p) { t[p] = max(t[lc(p)], t[rc(p)]); }

    void modify(int p, int l, int r, int x, int val) {
        if (l == r) return t[p] = val, void();
        int mid = (l + r) >> 1;
        if (x <= mid)
            modify(lson, x, val);
        else
            modify(rson, x, val);
        pushup(p);
    }

    int query(int p, int l, int r, int x, int y) {
        if (x < 1) x = 1;
        if (y > n) y = n;
        if (x > y) return -INF;
        if (x <= l && r <= y) return t[p];
        int mid = (l + r) >> 1, res = -INF;
        if (x <= mid) res = max(res, query(lson, x, y));
        if (y > mid) res = max(res, query(rson, x, y));
        return res;
    }
} t1, t2;

int val1[MAXN], val2[MAXN];

struct SGT {
    struct Node {
        int mx1, mx2, res;
    } t[MAXN << 2];

    Node merge(Node l, Node r) { return {max(l.mx1, r.mx1), max(l.mx2, r.mx2), max({l.res, r.res, l.mx1 + r.mx2})}; }

    void pushup(int p) { t[p] = merge(t[lc(p)], t[rc(p)]); }

    void build(int p, int l, int r) {
        if (l == r) return t[p] = {val1[l], val2[l], val1[l] + val2[l]}, void();
        int mid = (l + r) >> 1;
        build(lson), build(rson);
        pushup(p);
    }

    Node query(int p, int l, int r, int x, int y) {
        if (x <= l && r <= y) return t[p];
        int mid = (l + r) >> 1;
        if (y <= mid) return query(lson, x, y);
        if (x > mid) return query(rson, x, y);
        return merge(query(lson, x, y), query(rson, x, y));
    }
} T;

int a[4][MAXN], sum[4][MAXN], f[MAXN];
struct Query {
    int l, r, w;
    Query(int L, int R, int W) : l(L), r(R), w(W) {}
};
vector<Query> qry[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> q;
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j], sum[i][j] = sum[i][j - 1] + a[i][j];
    for (int i = 1, l, r, w; i <= q; i++) {
        cin >> l >> r >> w;
        qry[r].emplace_back(l, r, w);
    }

    int ans = -INF;
    for (int i = 1; i <= n; ++i) val1[i] = sum[1][i] - sum[2][i - 1], val2[i] = sum[3][n] - sum[3][i - 1] + sum[2][i];
    T.build(1, 1, n);
    for (int i = 1; i <= n; i++)
        for (auto [l, r, w] : qry[i]) ans = max(ans, T.query(1, 1, n, l, r).res - w);

    for (int i = 1; i <= n; i++) t2.modify(1, 1, n, i, sum[1][i] - sum[2][i - 1]);
    for (int i = 1; i <= n; i++) {
        f[i] = -INF;
        for (auto [l, r, w] : qry[i])
            f[i] =
                max({f[i], t1.query(1, 1, n, l - 1, r - 1) + sum[2][i] - w, t2.query(1, 1, n, l, r) + sum[2][i] - w});
        t1.modify(1, 1, n, i, f[i] - sum[2][i]);
    }
    for (int i = 1; i <= n; i++) f[i] -= sum[2][i];

    for (int i = 1; i <= n; ++i) val1[i] = f[i];
    T.build(1, 1, n);
    for (int i = 1; i <= n; i++)
        for (auto [l, r, w] : qry[i]) ans = max(ans, T.query(1, 1, n, max(1ll, l - 1), r).res - w);

    cout << ans << '\n';

    return 0;
}