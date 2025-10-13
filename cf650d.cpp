#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 8e5 + 10;
int n, m, res, L[MAXN], R[MAXN], a[MAXN], num[MAXN], ans[MAXN], cnt, vis[MAXN];

struct Node {
    int id, x, val, f, g;
    bool operator<(const Node &o) const { return x == o.x ? val < o.val : x < o.x; }
} qry[MAXN];

namespace fenwick {
    int t[MAXN];

    void init() { memset(t, 0, sizeof(t)); }

    constexpr int lowbit(int x) { return x & -x; }

    void add(int x, int val) {
        for (; x < MAXN; x += lowbit(x)) t[x] = max(t[x], val);
    }

    int query(int x) {
        int res = 0;
        for (; x; x -= lowbit(x)) res = max(res, t[x]);
        return res;
    }
} // namespace fenwick

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    cnt = n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    memcpy(num, a, sizeof(a));
    for (int i = 1; i <= m; i++) {
        qry[i].id = i;
        cin >> qry[i].x >> qry[i].val;
        num[++cnt] = qry[i].val;
    }
    sort(num + 1, num + cnt + 1);
    cnt = unique(num + 1, num + cnt + 1) - num - 1;
    for (int i = 1; i <= n; i++) a[i] = lower_bound(num + 1, num + cnt + 1, a[i]) - num;
    for (int i = 1; i <= m; i++) qry[i].val = lower_bound(num + 1, num + cnt + 1, qry[i].val) - num;
    for (int i = 1; i <= n; i++) {
        L[i] = fenwick::query(a[i] - 1) + 1;
        fenwick::add(a[i], L[i]);
    }
    fenwick::init();
    for (int i = n; i; i--) {
        R[i] = fenwick::query(cnt - a[i]) + 1;
        fenwick::add(cnt - a[i] + 1, R[i]);
    }
    for (int i = 1; i <= n; i++) res = max(res, L[i] + R[i] - 1);
    for (int i = 1; i <= n; i++)
        if (L[i] + R[i] - 1 == res) vis[L[i]]++;
    sort(qry + 1, qry + m + 1);
    fenwick::init();
    int nw = 1;
    for (int i = 1; i <= m; i++) {
        auto &[id, x, val, f, g] = qry[i];
        for (; nw < x; nw++) fenwick::add(a[nw], L[nw]);
        f = fenwick::query(val - 1);
    }
    fenwick::init();
    nw = n;
    for (int i = m; i; i--) {
        auto &[id, x, val, f, g] = qry[i];
        for (; nw > x; nw--) fenwick::add(cnt - a[nw] + 1, R[nw]);
        g = fenwick::query(cnt - val);
        if (f + g + 1 > res) ans[id] = f + g + 1;
    }
    for (int i = 1; i <= m; i++) {
        auto [id, x, val, f, g] = qry[i];
        if (!ans[id]) {
            if (L[x] + R[x] - 1 == res && vis[L[x]] == 1 && f + g + 1 < res)
                ans[id] = res - 1;
            else
                ans[id] = res;
        }
    }
    for (int i = 1; i <= m; i++) cout << ans[i] << '\n';

    return 0;
}