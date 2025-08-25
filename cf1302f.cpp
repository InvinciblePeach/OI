#include <bits/stdc++.h>
#define int long long
#define lc(p) p << 1
#define rc(p) p << 1 | 1

using namespace std;
typedef long long ll;

const int MAXN = 55, MAXM = 2e4 + 10;
int n, m, k, len, ans, g[MAXN][MAXM], dp[MAXN][MAXM], sum[MAXN][MAXM];

struct Node {
    int l, r;
    int val, add;
} t[MAXM << 2];

void pushup(int p) { t[p].val = max(t[lc(p)].val, t[rc(p)].val); }

void pushdown(int p) {
    t[lc(p)].val += t[p].add;
    t[rc(p)].val += t[p].add;
    t[lc(p)].add += t[p].add;
    t[rc(p)].add += t[p].add;
    t[p].add = 0;
}

void build(int p, int l, int r, int d) {
    t[p] = {l, r, 0, 0};
    if (l == r) return t[p].val = dp[d - 1][l] + sum[d][l + k - 1] - sum[d][l - 1], void();
    int mid = l + r >> 1;
    build(lc(p), l, mid, d), build(rc(p), mid + 1, r, d), pushup(p);
}

void modify(int p, int l, int r, int val) {
    if (l <= t[p].l && t[p].r <= r) return t[p].val += val, t[p].add += val, void();
    pushdown(p);
    if (l <= t[lc(p)].r) modify(lc(p), l, r, val);
    if (r >= t[rc(p)].l) modify(rc(p), l, r, val);
    pushup(p);
}

void add(int d, int p) {
    if (p) modify(1, max(1ll, p - k + 1), min(len, p), -g[d][p]);
}

void del(int d, int p) {
    if (p) modify(1, max(1ll, p - k + 1), min(len, p), g[d][p]);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> k;
    len = m - k + 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> g[i][j], sum[i][j] = sum[i][j - 1] + g[i][j];
    for (int i = 1; i <= n; i++) {
        build(1, 1, len, i);
        if (i > 1)
            for (int j = 1; j < k; j++)
                add(i, j);
        for (int j = 1; j + k - 1 <= m; j++) {
            int l = j, r = j + k - 1;
            if (i == 1)
                dp[1][j] = sum[1][r] - sum[1][l - 1];
            else
                del(i, l - 1), add(i, r), dp[i][j] = sum[i][r] - sum[i][l - 1] + t[1].val;
        }
    }

    for (int i = 1; i <= len; i++) ans = max(ans, dp[n][i]);
    cout << ans << '\n';
    return 0;
}