#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int t, n, a[MAXN], ans;

void solve() {
    cin >> n;
    int k = 0;
    for (int i = 1, q; i <= n; i++) {
        cin >> q;
        if (q == a[k]) continue;
        else a[++k] = q;
    }
    ans = 0, a[0] = a[k + 1] = 0;
    for (int i = 1; i <= k; i++) {
        if (a[i - 1] < a[i] && a[i] > a[i + 1]) ans++;
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> t;
    while (t --> 0) {
        solve();
    }

    return 0;
}