#include <bits/stdc++.h>
#define lc(p) t[p].lc
#define rc(p) t[p].rc
#define lson lc(p), l, mid
#define rson rc(p), mid + 1, r

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 3e5 + 10, MAXL = 2e8 + 10;
int n, m, q, rt, num, cnt, ans[MAXN];
multiset<int> pos[MAXN];

struct Node {
    int lc, rc, mn;
    multiset<int> pre;
} t[MAXN << 5];

void pushup(int p) { t[p].mn = min(t[lc(p)].mn, t[rc(p)].mn); }

struct Query {
    int pos, tim, id, typ;
    bool operator<(const Query &o) const { return tim == o.tim ? typ < o.typ : tim < o.tim; }
} qry[MAXN << 2];

int tot;
void modify(int &p, int l, int r, int pos, int val, int typ) {
    if (!p) p = ++tot;
    if (l == r) {
        auto &pre = t[p].pre;
        if (typ)
            pre.emplace(val);
        else
            pre.erase(pre.find(val));
        if (!pre.empty())
            t[p].mn = *pre.begin();
        else
            t[p].mn = MAXL;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) modify(lson, pos, val, typ);
    if (pos > mid) modify(rson, pos, val, typ);
    pushup(p);
}

int query(int p, int l, int r, int pos, int res) {
    if (l == r) return l - pos;
    int mid = (l + r) >> 1, tmp = min(res, t[rc(p)].mn);
    // cerr << r << ' ' << res << '\n';
    if (pos > mid || tmp < (pos << 1) - mid) return query(rson, pos, res);
    return query(lson, pos, tmp);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> q;
    t[0].mn = MAXL;
    for (int i = 1; i <= m; i++) {
        pos[i].emplace(-MAXL), pos[i].emplace(MAXL);
        modify(rt, 1, MAXL, MAXL, -MAXL, 1);
    }
    for (int i = 1, x, t, a, b; i <= n; i++) {
        cin >> x >> t >> a >> b;
        qry[++cnt] = {x, a, t, 1};
        qry[++cnt] = {x, b + 1, t, 0};
    }
    for (int i = 1, pos, tim; i <= q; i++) {
        cin >> pos >> tim;
        qry[++cnt] = {pos, tim, i, 2};
    }
    sort(qry + 1, qry + 1 + cnt);
    for (int i = 1; i <= cnt; i++) {
        auto [pos, tim, id, typ] = qry[i];
        if (typ == 0) {
            auto l = --::pos[id].lower_bound(pos), r = ++::pos[id].lower_bound(pos);
            modify(rt, 1, MAXL, *r, pos, 0);
            modify(rt, 1, MAXL, *r, *l, 1);
            modify(rt, 1, MAXL, pos, *l, 0);
            ::pos[id].erase(::pos[id].find(pos));
            if (::pos[id].size() == 2) num--;
        }
        if (typ == 1) {
            auto l = --::pos[id].lower_bound(pos), r = ::pos[id].lower_bound(pos);
            modify(rt, 1, MAXL, *r, pos, 1);
            modify(rt, 1, MAXL, *r, *l, 0);
            modify(rt, 1, MAXL, pos, *l, 1);
            ::pos[id].emplace(pos);
            if (::pos[id].size() == 3) num++;
        }
        if (typ == 2) {
            if (num < m) {
                ans[id] = -1;
                continue;
            }
            ans[id] = query(rt, 1, MAXL, pos, MAXL);
        }
    }
    for (int i = 1; i <= q; i++) cout << ans[i] << '\n';

    return 0;
}