#include <bits/stdc++.h>
#define lc(x) x << 1
#define rc(x) x << 1 | 1

using namespace std;
typedef long long LL;
typedef double ld;

const int MAXN = 5e5 + 10;
const LL INF = 0x3f3f3f3f3f3f3f3f;
int n, m, tot, cnt, dfn[MAXN], chg[MAXN], a[MAXN], val[MAXN];
LL ans[MAXN], c[MAXN];
vector<int> g[MAXN], L[MAXN], R[MAXN];

ld K(int x, int y) { return (ld(val[x]) * val[x] + ld(c[x]) - ld(val[y]) * val[y] - ld(c[y])) / ld(val[x] - val[y]); }

struct Node {
    int L = 0, R = -1;
    vector<int> q;
} t[MAXN << 2];

void dfs(int u, int fa) {
    dfn[u] = ++tot;
    if (chg[u] > 0) L[chg[u]].emplace_back(tot); 
    if (chg[u] < 0) R[-chg[u]].emplace_back(tot - 1); 
    for (auto v : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
    }
    if (chg[u] > 0) R[chg[u]].emplace_back(tot); 
    if (chg[u] < 0) L[-chg[u]].emplace_back(tot + 1); 
}

void modify(int p, int l, int r, int ll, int rr, int x) {
    if (l <= ll && rr <= r) {
        int &L = t[p].L, &R = t[p].R;
        auto &q = t[p].q;
        q.resize(R + 5);
        if (L <= R && val[q[R]] == val[x]) {
            if (c[q[R]] <= c[x]) return;
            R--;
        }
        while (L < R && K(q[R], x) < K(q[R], q[R - 1])) R--;
        return q[++R] = x, void();
    }

    int mid = (ll + rr) >> 1;
    if (l <= mid) modify(lc(p), l, r, ll, mid, x);
    if (r > mid) modify(rc(p), l, r, mid + 1, rr, x);
}

LL query(int p, int ll, int rr, int pos, int x, LL res) {
    LL tmp = INF;
    int &L = t[p].L, &R = t[p].R;
    auto &q = t[p].q;
    while (L < R && K(q[L], q[L + 1]) <= 2 * ld(x)) L++;
    if (L <= R) tmp = LL(x - val[q[L]]) * (x - val[q[L]]) + c[q[L]];
    tmp = min(res, tmp);
    if (ll == rr) return tmp;
    int mid = (ll + rr) >> 1;
    if (pos <= mid) return query(lc(p), ll, mid, pos, x, tmp);
    else return query(rc(p), mid + 1, rr, pos, x, tmp);
}

struct Query{
    int s, val, id;

    bool operator<(const Query &o) const { return val < o.val; }
} qry[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> c[0];
    for (int i = 1; i < n; i++) {
        static int opt, u, id, y, z;
        cin >> opt >> u >> id;
        if (opt == 0) {
            cin >> val[id] >> y >> z >> c[id];
            chg[i] = id;
        } else {
            chg[i] = -id;
        }
        g[u].emplace_back(i);
        g[i].emplace_back(u);
    }
    dfs(0, 0);
    for (int i = 1; i <= n; i++) a[i] = i;
    sort(a + 1, a + 1 + n, [](int x, int y) -> bool { return val[x] < val[y]; });
    modify(1, 1, n, 1, n, 0);
    for (int k = 1; k <= n; k++) {
        int i = a[k];
        for (int j = 0; j < int(L[i].size()); j++) {
            auto [l, r] = pair(L[i][j], R[i][j]);
            if (l <= r) modify(1, l, r, 1, n, i);
        }
    }
    for (int i = 1; i <= m; i++)
        cin >> qry[i].s >> qry[i].val, qry[i].id = i;
    sort(qry + 1, qry + 1 + m);
    for (int i = 1; i <= m; i++)
        ans[qry[i].id] = query(1, 1, n, dfn[qry[i].s], qry[i].val, INF);
    for (int i = 1; i <= m; i++) cout << ans[i] << '\n';

    return 0;
}