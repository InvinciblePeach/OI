#include <bits/stdc++.h>
#define int unsigned long long

using namespace std;
typedef long long ll;

int T, n, l, r, k;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        cin >> n >> l >> r >> k;
        if (n == 2) {
            cout << "-1\n";
            continue;
        }
        if (n & 1) {
            cout << l << '\n';
            continue;
        }
        int t = 0;
        for (int i = 0; i < 63; i++) if (l >> i & 1) t = i;
        int ans = (1 << (t + 1));
        assert(ans > l);
        if (ans <= r) {
            if (k <= n - 2) cout << l << '\n';
            else cout << ans << '\n';
        }
        else cout << "-1\n";
    }

    return 0;
}