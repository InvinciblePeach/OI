#include <bits/stdc++.h>
#define int long long

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
        if ((n & 1) || k <= n - 2) {
            cout << l << '\n';
            continue;
        }
        int H = 63 - __builtin_clzll(l);
        ll u = 1ll << (H + 1);
        if (u <= r) cout << u << '\n';
        else cout << "-1\n";
    }

    return 0;
}