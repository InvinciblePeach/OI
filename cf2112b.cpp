#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1010;
int T, n, a[MAXN], ans;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        cin >> n;
        ans = -1;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i < n; i++)
            if (abs(a[i + 1] - a[i]) <= 1) {
                ans = 0;
                break;
            }
        if (ans == -1) {
            for (int i = 1; i <= n - 2; i++) {
                if ((a[i + 2] >= a[i] && a[i + 1] <= a[i]) || (a[i + 1] >= a[i] && a[i + 2] <= a[i])) ans = 1;
            }
            reverse(a + 1, a + 1 + n);
            for (int i = 1; i <= n - 2; i++) {
                if ((a[i + 2] >= a[i] && a[i + 1] <= a[i]) || (a[i + 1] >= a[i] && a[i + 2] <= a[i])) ans = 1;
            }
        }
        cout << ans << '\n';
    }

    return 0;
}