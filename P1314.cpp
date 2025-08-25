#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10, MAXW = 1e6;
int n, m, s, res, ans = LLONG_MAX, w[MAXN], v[MAXN], l[MAXN], r[MAXN];

bool check(int nw) {
    res = 0;
    static int a[MAXN], b[MAXN];
    memset(a, 0, sizeof(a)), memset(b, 0, sizeof(b));
    for (int i = 1; i <= n; i++)
        a[i] = a[i - 1] + bool(w[i] >= nw),
        b[i] = b[i - 1] + bool(w[i] >= nw) * v[i];
    for (int i = 1; i <= m; i++)
        res += (a[r[i]] - a[l[i] - 1]) * (b[r[i]] - b[l[i] - 1]);
    return res > s;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> s;
    for (int i = 1; i <= n; i++) cin >> w[i] >> v[i];
    for (int i = 1; i <= m; i++) cin >> l[i] >> r[i];

    int l = 1, r = MAXW;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) l = mid + 1;
        else r = mid;
        ans = min(ans, llabs(res - s));
    }
    cout << ans << '\n';


    return 0;
}