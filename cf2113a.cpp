#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int T, k, a, b, x, y, ans;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        cin >> k >> a >> b >> x >> y;
        ans = 0;
        if (x > y) swap(x, y), swap(a, b);
        if (k >= a) {
        ans += (k - a + x) / x;
        k -= (k - a + x) / x * x;
        }
        if (k >= b) {
        ans += (k - b + y) / y;
        }
        cout << ans << '\n';
    }

    return 0;
}