#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll n, m, ans;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (ll i = 0, t = 1; i <= m; i++) {
        ans += t;
        t *= n;
        if (ans > 1e9) {
            cout << "inf\n";
            return 0;
        }
    }
    cout << ans << '\n';

    return 0;
}