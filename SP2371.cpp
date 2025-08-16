#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
int n, dp[MAXN], num[MAXN << 1], cnt;

struct Node {
    int id, x, y;

    bool operator<(const Node &o) const { return x < o.x; }
} q[MAXN], tmp[MAXN];

namespace fenwick {
    int t[MAXN << 1];

    constexpr int lowbit(const int &x) { return x & -x; }

    void add(int x, int val) {
        for (; x <= cnt; x += lowbit(x)) t[x] = max(t[x], val);
    }

    int query(int x) {
        int res = 0;
        for (; x; x -= lowbit(x)) res = max(res, t[x]);
        return res;
    }

    void clear(int x) {
        for (; x <= cnt; x += lowbit(x)) t[x] = 0;
    }
} // namespace fenwick

void solve(int l, int r) {
    if (l == r) return dp[l] = 1, void();
    int mid = (l + r) >> 1;
    solve(l, mid);
    for (int i = mid + 1; i <= r; i++) tmp[i] = q[i];
    sort(tmp + mid + 1, tmp + 1 + r);
    int i = l, j = mid + 1;
    for (; j <= r; j++) {
        for (; i <= mid && q[i].x < tmp[j].x; i++) fenwick::add(q[i].y, dp[q[i].id]);
        dp[tmp[j].id] = max(dp[tmp[j].id], fenwick::query(tmp[j].y - 1) + 1);
    }
    for (int k = l; k < i; k++) fenwick::clear(q[i].y);
    solve(mid + 1, r);
    inplace_merge(q + l, q + 1 + mid, q + r + 1);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> q[i].x >> q[i].y;
        num[++cnt] = q[i].x, num[++cnt] = q[i].y;
        q[i].id = i;
    }
    sort(num + 1, num + 1 + cnt);
    cnt = unique(num + 1, num + 1 + cnt) - num - 1;
    for (int i = 1; i <= n; i++) {
        q[i].x = lower_bound(num + 1, num + 1 + cnt, q[i].x) - num;
        q[i].y = lower_bound(num + 1, num + 1 + cnt, q[i].y) - num;
    }
    solve(1, n);
    int ans = 0;
    for (int i = 1; i <= n; i++) ans = max(dp[i], ans);
    cout << ans << '\n';
    return 0;
}