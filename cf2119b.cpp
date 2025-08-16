#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 1e3 + 10;
int T, n, px, py, qx, qy, a[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        int sum = 0, mx = 0;
        cin >> n >> px >> py >> qx >> qy;
        for (int i = 1; i <= n; i++) cin >> a[i], sum += a[i], mx = max(mx, a[i]);
        int tmp = max(0ll, 2 * mx - sum), d = (px - qx) * (px - qx) + (py - qy) * (py - qy);
        if (sum * sum >= d && tmp * tmp <= d) cout << "Yes\n";
        else cout << "No\n";
    }

    return 0;
}