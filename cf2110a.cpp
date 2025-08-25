#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 110;
int T, n, a[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        sort(a + 1, a + 1 + n);
        int ans = MAXN;
        for (int i = 1; i <= n; i++) {
            if (!((a[i] ^ a[n]) & 1)) {
                ans = i - 1;
                break;
            }
        }
        for (int i = n; i; i--) {
            if (!((a[1] ^ a[i]) & 1)) {
                ans = min(ans, n - i);
                break;
            }
        }
        cout << ans << '\n';
    }

    return 0;
}