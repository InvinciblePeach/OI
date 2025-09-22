#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 3e7 + 10;
int n, m, a[MAXN], mx, mn, id, ans, p;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int T;
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        mx = 0;
        for (int i = 1; i <= n; i++) {
            if (mx < a[i]) mx = a[i], id = i;
        }
        p = id;
        for (int i = 1; i <= n; i++) {
            if (!--p) p = n;
            if (a[id] - a[p] > m) {
                if (++p > n) p = 1;
                break;
            }
        }
        mx = mn = a[p], ans = 1, id = p;
        for (int i = 1; i < n; i++) {
            if (++id > n) id = 1;
            mx = max(mx, a[id]), mn = min(mn, a[id]);
            if (mx - mn > m) {
                mx = mn = a[id];
                ans++;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
