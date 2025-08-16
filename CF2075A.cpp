#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int t, n, k;

void solve() {
    int ans = 0;
    cin >> n >> k;
    if (n & 1) n -= k + ((k & 1) == 0), ans++;
    k -= (k & 1);
    ans += (n - 1 + k) / k;
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> t;
    while (t --> 0) solve();

    return 0;
}