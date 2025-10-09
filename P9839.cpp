#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 2e5 + 10, INF = 0x3f3f3f3f;
int n, m, k, a[MAXN], flag;
set<int> pos[MAXN];

int find(int l, int r, int val) {
    auto &st = pos[val];
    auto it = st.upper_bound(l);
    if (it == st.end() || *it > r) return 0;
    return *it;
}

int get(int l, int r, int val, int tag) {
    auto id = find(l + tag, r, val);
    if (!id) return INF;
    if ((id & 1) == (l & 1)) return id;
    auto nxt = find(id, r, val);
    if (!nxt) return (l & 1) == flag ? id : INF;
    if ((nxt & 1) == (l & 1)) return id;
    return INF;
}

#define lc(p) p << 1
#define rc(p) p << 1 | 1
struct Node {
    int l, r, mn, pos;
} t[MAXN << 2];

Node merge(const Node &l, const Node &r) {
    Node res;
    res.l = l.l, res.r = r.r;
    if (l.mn < r.mn)
        res.mn = l.mn, res.pos = l.pos;
    else
        res.mn = r.mn, res.pos = r.pos;
    return res;
}

void pushup(int p) { t[p] = merge(t[lc(p)], t[rc(p)]); }

void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    if (l == r) return t[p].mn = INF, t[p].pos = l, void();

    int mid = (l + r) >> 1;
    build(lc(p), l, mid), build(rc(p), mid + 1, r);
    pushup(p);
}

void modify(int p, int pos, int val) {
    if (t[p].l == t[p].r) return t[p].mn = val, void();

    if (pos <= t[lc(p)].r)
        modify(lc(p), pos, val);
    else
        modify(rc(p), pos, val);
    pushup(p);
}

Node query(int p, int l, int r) {
    if (l <= t[p].l && t[p].r <= r) return t[p];

    if (r <= t[lc(p)].r) return query(lc(p), l, r);
    if (l >= t[rc(p)].l) return query(rc(p), l, r);
    return merge(query(lc(p), l, r), query(rc(p), l, r));
}

int ans[2][MAXN];
vector<int> pnt[MAXN];
struct Query {
    int x, y, l, r, id;

    Query(int X, int Y, int L, int R, int ID) : x(X), y(Y), l(L), r(R), id(ID) {}
};
vector<Query> qry[MAXN];

int calc(int x, int y, int l, int r) {
    if (x == y) {
        int nxt = find(l - 1, r, x);
        if (!nxt) return flag ? 1 : -1;
        if ((nxt & 1) == (l & 1)) return 1;
        return -1;
    }
    if (y == a[l]) {
        int nxt = find(l, r, y);
        if (nxt && (nxt & 1) == (l & 1)) return 1;
        if (!nxt) return flag ? 1 : -1;
    }
    int wx = get(l - 2, r, x, 1), wy = get(l - 1, r, y, 0);
    int res = min(wx, wy), pos = (wx < wy ? l - 2 : l - 1);
    auto tmp = query(1, l, r);
    if (tmp.mn < res) res = tmp.mn, pos = tmp.pos;
    if (res == INF) return flag ? 1 : -1;
    return (l & 1) == (pos & 1) ? 1 : -1;
}

void solve() {
    build(1, 1, n);
    for (int r = 1; r <= n; r++) {
        for (auto x : pnt[r]) modify(1, x, get(x, r, a[x], 0));
        for (auto [x, y, l, r, id] : qry[r]) ans[flag][id] = calc(x, y, l, r);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) cin >> a[i], pos[a[i]].emplace(i);
    for (int i = 1, x, y, l, r; i <= m; i++) {
        cin >> x >> y >> l >> r;
        qry[r].emplace_back(x, y, l, r, i);
    }
    for (int i = 1; i <= n; i++) {
        int nxt = find(i, n, a[i]);
        if (!nxt) continue;
        pnt[nxt].emplace_back(i);
        int nnxt = find(nxt, n, a[i]);
        if (nnxt) pnt[nnxt].emplace_back(i);
    }
    for (; flag < 2; flag++) solve();
    for (int i = 1; i <= m; i++) {
        if (ans[1][i] == -1)
            cout << "B\n";
        else if (ans[0][i] == 1)
            cout << "A\n";
        else
            cout << "D\n";
    }
    return 0;
}