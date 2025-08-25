#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 5010;
int T, n, k, a[MAXN], ans;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        cin >> n >> k;
        ans = 0;
        for (int i = 1; i <= n; i++) cin >> a[i], ans += __builtin_popcountll(a[i]);
        for (int j = 0; j <= 62 && k >= (1ll << j); j++) {
            for (int i = 1; i <= n && k >= (1ll << j); i++) {
                if (a[i] >> j & 1) continue;
                a[i] |= 1ll << j, ans++, k -= 1ll << j;
            }
        }
        cout << ans << '\n';
    }

    return 0;
}