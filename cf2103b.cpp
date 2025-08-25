#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int T, n;
char a[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    auto calc = [=]() -> int {
        int res = n;
        for (int i = 1; i <= n; i++) res += (a[i - 1] ^ a[i]);
        // for (int i = 1; i <= n; i++) cerr << int(a[i]) << " \n"[i == n];
        return res;
    };
    while (T --> 0) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i], a[i] -= '0';
        int ans = calc();
        int l = -1, r = -1;
        for (int i = 1; i <= n; i++) {
            if (a[i - 1] == 0 && a[i] == 1) {
                if (~l) {
                    r = i;
                    break;
                }
                else l = i;
            }
        }
        if (l != -1) {
            if (r == -1) r = n + 1;
            reverse(a + l, a + r);
            ans = min(ans, calc());
            reverse(a + l, a + r);
        }
        l = r = -1;
        for (int i = 1; i <= n; i++) {
            if (a[i - 1] == 1 && a[i] == 0) {
                if (~l) {
                    r = i;
                    break;
                }
                else l = i;
            }
        }
        if (l != -1) {
            if (r == -1) r = n + 1;
            reverse(a + l, a + r);
            ans = min(ans, calc());
            reverse(a + l, a + r);
        }
        cout << ans << '\n';
    }

    return 0;
}