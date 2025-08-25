#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

const int MAXN = 1e4 + 10;
const ld eps = 1e-9;
int T, n, a[MAXN], b[MAXN], c[MAXN];

ld f(ld x) {
    ld res = -1.0/0.0;
    // cerr << res << '\n';
    for (int i = 1; i <= n; i++) res = max(res, a[i] * x * x + b[i] * x + c[i]);
    return res;
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i] >> c[i];

    ld l = 0, r = 1000;
    while (r - l > eps) {
        ld mid1 = (2 * l + r) / 3;
        ld mid2 = (l + 2 * r) / 3;
        if (f(mid1) < f(mid2)) r = mid2;
        else l = mid1;
    }
    printf("%.4Lf\n", f(l));
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T-- > 0) solve();

    return 0;
}