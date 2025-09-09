#include <bits/stdc++.h>
#define lc(p) p << 1
#define rc(p) p << 1 | 1

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 5.5e5 + 10;
int n, m1, m2, a[MAXN], pos[MAXN];
int dp[MAXN], pre[MAXN], ans[MAXN];

struct Point {
    int l, r;
} pnt[2][2][MAXN];

struct Node {
    int l, r;
    int mx, tag;
} t[MAXN << 2];

void pushup(int p) { t[p].mx = max(t[lc(p)].mx, t[rc(p)].mx); }

void pushdown(int p) {
    auto &tag = t[p].tag;
    t[lc(p)].mx += tag, t[rc(p)].mx += tag;
    t[lc(p)].tag += tag, t[rc(p)].tag += tag;
    tag = 0;
}

void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(lc(p), l, mid), build(rc(p), mid + 1, r);
}

void modify(int p, int l, int r, int val) {
    if (l > r) return;
    if (l <= t[p].l && t[p].r <= r) return t[p].mx += val, t[p].tag += val, void();

    pushdown(p);
    if (l <= t[lc(p)].r) modify(lc(p), l, r, val);
    if (r >= t[rc(p)].l) modify(rc(p), l, r, val);
    pushup(p);
}

int query(int p, int pos) {
    if (t[p].l == t[p].r) return t[p].mx;

    pushdown(p);
    if (pos <= t[lc(p)].r) return query(lc(p), pos);
    return query(rc(p), pos);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], pos[a[i]] = i;
    {
        for (int i = 1; i <= n; i++) dp[i] = n + 1;
        for (int i = 1; i <= n; i++) {
            int p = lower_bound(dp + 1, dp + 1 + n, a[i]) - dp;
            pnt[0][0][i] = {a[i], dp[p] - 1};
            dp[p] = a[i];
        }
        for (int i = 1; i <= n; i++)
            if (dp[i] <= n) m1++;
    }
    {
        for (int i = 1; i <= n; i++) dp[i] = n + 1;
        for (int i = 1; i <= n; i++) {
            int p = lower_bound(dp + 1, dp + 1 + n, n - a[i] + 1) - dp;
            pnt[0][1][i] = {n - dp[p] + 2, a[i]};
            dp[p] = n - a[i] + 1;
        }
        for (int i = 1; i <= n; i++)
            if (dp[i] <= n) m2++;
    }
    {
        for (int i = 1; i <= n; i++) dp[i] = n + 1;
        for (int i = n; i; i--) {
            int p = lower_bound(dp + 1, dp + 1 + n, a[i]) - dp;
            pnt[1][0][i] = {a[i], dp[p] - 1};
            dp[p] = a[i];
        }
    }
    {
        for (int i = 1; i <= n; i++) dp[i] = n + 1;
        for (int i = n; i; i--) {
            int p = lower_bound(dp + 1, dp + 1 + n, n - a[i] + 1) - dp;
            pnt[1][1][i] = {n - dp[p] + 2, a[i]};
            dp[p] = n - a[i] + 1;
        }
    }

    build(1, 1, n - 1);
    for (int i = 1; i <= n; i++) {
        modify(1, pnt[1][0][i].l, min(pnt[1][0][i].r, n - 1), 1);
        modify(1, max(1, pnt[1][1][i].l - 1), pnt[1][1][i].r - 1, 1);
    }
    for (int i = 1; i < n; i++) {
        modify(1, pnt[0][0][i].l, min(pnt[0][0][i].r, n - 1), 1);
        modify(1, max(1, pnt[0][1][i].l - 1), pnt[0][1][i].r - 1, 1);
        modify(1, pnt[1][0][i].l, min(pnt[1][0][i].r, n - 1), -1);
        modify(1, max(1, pnt[1][1][i].l - 1), pnt[1][1][i].r - 1, -1);
        if (t[1].mx == m1 + m2) {
            int pos;
            for (int j = 1; j < n; j++)
                if (query(1, j) == m1 + m2) pos = j;
            {
                {
                    for (int j = 1; j <= n; j++) dp[j] = n + 1;
                    for (int j = 1; j <= i; j++) {
                        if (a[j] <= pos) {
                            int p = lower_bound(dp + 1, dp + 1 + n, a[j]) - dp;
                            pre[j] = ::pos[dp[p - 1]];
                            dp[p] = a[j];
                        }
                    }
                    int res = 0;
                    for (int j = 1; j <= n; j++)
                        if (dp[j] <= n) res++;
                    for (int j = ::pos[dp[res]]; j; j = pre[j]) ans[res--] = j;
                }
                {
                    for (int j = 1; j <= n; j++) dp[j] = n + 1;
                    for (int j = n; j > i; j--) {
                        if (a[j] > pos) {
                            int p = lower_bound(dp + 1, dp + 1 + n, n - a[j] + 1) - dp;
                            pre[j] = ::pos[n - dp[p - 1] + 1];
                            dp[p] = n - a[j] + 1;
                        }
                    }
                    int res = 0;
                    for (int j = 1; j <= n; j++)
                        if (dp[j] <= n) res++;
                    for (int j = ::pos[n - dp[res] + 1]; j; j = pre[j]) ans[m1 - --res] = j;
                }
                cout << m1 << '\n';
                for (int j = 1; j <= m1; j++) cout << ans[j] << " \n"[j == m1];
            }
            {
                {
                    for (int j = 1; j <= n; j++) dp[j] = n + 1;
                    for (int j = 1; j <= i; j++) {
                        if (a[j] > pos) {
                            int p = lower_bound(dp + 1, dp + 1 + n, n - a[j] + 1) - dp;
                            pre[j] = ::pos[n - dp[p - 1] + 1];
                            dp[p] = n - a[j] + 1;
                        }
                    }
                    int res = 0;
                    for (int j = 1; j <= n; j++)
                        if (dp[j] <= n) res++;
                    for (int j = ::pos[n - dp[res] + 1]; j; j = pre[j]) ans[res--] = j;
                }
                {
                    for (int j = 1; j <= n; j++) dp[j] = n + 1;
                    for (int j = n; j > i; j--) {
                        if (a[j] <= pos) {
                            int p = lower_bound(dp + 1, dp + 1 + n, a[j]) - dp;
                            pre[j] = ::pos[dp[p - 1]];
                            dp[p] = a[j];
                        }
                    }
                    int res = 0;
                    for (int j = 1; j <= n; j++)
                        if (dp[j] <= n) res++;
                    for (int j = ::pos[dp[res]]; j; j = pre[j]) ans[m2 - --res] = j;
                }
                cout << m2 << '\n';
                for (int j = 1; j <= m2; j++) cout << ans[j] << " \n"[j == m2];
            }
            return 0;
        }
    }
    cout << "IMPOSSIBLE\n";

    return 0;
}