#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 510;
const double eps = 1e-5;
int n, m, ans, cnt, p[MAXN];
struct Node {
    double a[MAXN];
    int c;
    bool operator<(const Node &o) const { return c < o.c; }
} q[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> q[i].a[j];
    for (int i = 1; i <= n; i++) cin >> q[i].c;
    sort(q + 1, q + 1 + n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (fabs(q[i].a[j]) <= eps) continue;
            if (!p[j]) {
                p[j] = i;
                cnt++, ans += q[i].c;
                break;
            } else {
                double div = q[i].a[j] / q[p[j]].a[j];
                for (int k = j; k <= m; k++) q[i].a[k] -= div * q[p[j]].a[k];
            }
        }
    }
    cout << cnt << ' ' << ans << '\n';

    return 0;
}