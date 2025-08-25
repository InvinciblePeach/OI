#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;
int n, mn1 = INT_MAX, mn2 = INT_MAX, mn3 = INT_MAX, mn4 = INT_MAX, ans = INT_MAX;

struct Point {
    int x, y;
    bool operator<(const Point &o) { return x < o.x; }
} p[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i].x >> p[i].y;
        mn1 = min(mn1, p[i].x + p[i].y);
        mn2 = min(mn2, p[i].x - p[i].y);
        mn3 = min(mn3, p[i].y - p[i].x);
        mn4 = min(mn4, -p[i].x - p[i].y);
    }
    sort(p + 1, p + 1 + n);
    for (int i = 1; i <= n; i++) {
        int mx = max({p[i].x + p[i].y - mn1, p[i].x - p[i].y - mn2, p[i].y - p[i].x - mn3, -p[i].x - p[i].y - mn4});
        int mn = INT_MAX;
        for (int j = max(i - 500, 1); j <= min(i + 500, n); j++)
            if (j != i) mn = min(mn, abs(p[i].x - p[j].x) + abs(p[i].y - p[j].y));
        ans = min(ans, mx - mn);
    }
    cout << ans << '\n';

    return 0;
}