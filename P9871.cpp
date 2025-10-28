#include <bits/stdc++.h>
#define int long long
#define lc(p) p << 1
#define rc(p) p << 1 | 1
#define lson lc(p), l, mid
#define rson rc(p), mid + 1, r

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 2e5 + 10, MAXM = 1e6 + 10;
int n, m, k, d;

struct Node {
    int val, tag;
    void entag(int x) { val += x, tag += x; }
} t[MAXN << 2];

void pushup(int p) { t[p].val = max(t[lc(p)].val, t[rc(p)].val); }

void pushdown(int p) {
    auto &tag = t[p].tag;
    if (tag) {
        t[lc(p)].entag(tag);
        t[rc(p)].entag(tag);
        tag = 0;
    }
}

void build(int p, int l, int r) {
    t[p] = {0, 0};
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(lson), build(rson);
    pushup(p);
}

void modify(int p, int l, int r, int x, int y, int val) {
    if (x <= l && r <= y) return t[p].entag(val);
    pushdown(p);
    int mid = (l + r) >> 1;
    if (x <= mid) modify(lson, x, y, val);
    if (y > mid) modify(rson, x, y, val);
    pushup(p);
}

int query(int p, int l, int r, int x, int y) {
    if (x > y) return 0;
    if (x <= l && r <= y) return t[p].val;
    pushdown(p);
    int mid = (l + r) >> 1;
    if (y <= mid) return query(lson, x, y);
    if (x > mid) return query(rson, x, y);
    return max(query(lson, x, y), query(rson, x, y));
}

struct Query {
    int l, r, val;
    bool operator<(const Query &o) const { return r < o.r; }
} a[MAXN];

int num[MAXN], cnt;
void solve() {
    cnt = 0;
    cin >> n >> m >> k >> d;
    for (int i = 1, x, y, v; i <= m; i++) {
        cin >> x >> y >> v;
        a[i] = {x - y, x, v};
        num[++cnt] = x - y;
        num[++cnt] = x;
    }

    sort(num + 1, num + 1 + cnt);
    cnt = unique(num + 1, num + 1 + cnt) - num - 1;
    auto id = [=](int x) { return lower_bound(num + 1, num + 1 + cnt, x) - num; };
    for (int i = 1; i <= m; i++) a[i].l = id(a[i].l), a[i].r = id(a[i].r);
    sort(a + 1, a + 1 + m);

    int ans = 0;
    build(1, 0, cnt);
    for (int i = 1, j = 1; i <= cnt; i++) {
        modify(1, 0, cnt, 0, i - 1, -d * (num[i] - num[i - 1]));
        for (; j <= m && a[j].r <= i; j++) modify(1, 0, cnt, 0, a[j].l, a[j].val);
        ans = max(ans, query(1, 0, cnt, id(num[i] - k), i - 1));
        if (i + 1 <= cnt) modify(1, 0, cnt, i + 1, i + 1, ans);
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int T, id;
    cin >> id >> T;
    while (T-- > 0) solve();

    return 0;
}