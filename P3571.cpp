#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e6 + 10;
int n, m, mx, fa[MAXN], dep[MAXN], sum[MAXN], cnt[MAXN], ans[MAXN];
int l = 1, r = 1, q[MAXN];

struct Query {
    int k, id;
    bool operator<(const Query &o) const { return k < o.k; }
} qry[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> qry[i].k, qry[i].id = i;
    sort(qry + 1, qry + 1 + m);
    mx = dep[1] = sum[1] = 1;
    for (int i = 2; i <= n; i++) cin >> fa[i], sum[dep[i] = dep[fa[i]] + 1]++, mx = max(mx, dep[i]);
    for (int i = 1; i <= mx; i++) cnt[i] = n - (sum[i] += sum[i - 1]);
    for (int i = 1; i <= mx; i++) {
        while (l < r && (i - q[r]) * (cnt[q[r - 1]] - cnt[q[r]]) >= (q[r] - q[r - 1]) * (cnt[q[r]] - cnt[i])) r--;
        q[++r] = i;
    }
    for (int i = 1; i <= m; i++) {
        auto [k, id] = qry[i];
        while (l < r && (cnt[q[l]] - cnt[q[l + 1]]) < (q[l + 1] - q[l]) * k) l++;
        ans[id] = q[l] + (cnt[q[l]] - 1 + k) / k;
    }
    for (int i = 1; i <= m; i++) cout << ans[i] << " \n"[i == m];

    return 0;
}