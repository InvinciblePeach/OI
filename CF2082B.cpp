#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int t, x, n, m, cnt;

void solve() {
    cin >> x >> n >> m;
    int p = n, q = m;
    for (int i = 1; i <= p + q; i++) {
        if (x & 1) {
            if (n) x >>= 1, n--;
            else x = (x + 1) >> 1, m--;
        } else {
            x = (x + 1) >> 1, m--;
        }
    }
    cout << x << ' ';
    n = p, m = q;
    for (int i = 1; i <= p + q; i++) {
        if (x & 1) {
            if (m) x = (x + 1) >> 1, m--;
            else x >>= 1, n--;
        } else {
            x >>= 1, n--;
        }
    }
    cout << x << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> t;
    while (t --> 0) solve();

    return 0;
}