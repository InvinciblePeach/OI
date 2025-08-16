#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 5010;
int T, n, a[MAXN], ans;

int calc(int l, int r, int k) {
    int res = 0;
    for (; l <= r; r--)
        while (a[l] + a[r] > k)
            res += r - l++;
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        ans = 0;
        cin >> n;
        for (int i = 0; i < n; i++) cin >> a[i];
        reverse(a, a + n);
        if (n >= 3) {
            ans += calc(2, n - 1, max(a[1], 2 * a[0]) - a[0]);
            if (n >= 4) {
                ll D = max(a[2], 2 * a[0]) - a[0] - a[1];
                int L = 3, R = n - 1, pos = 2;
                while (L <= R) {
                    int m = (L + R) >> 1;
                    if (a[m] > D) {
                        pos = m;
                        L = m + 1;
                    } else {
                        R = m - 1;
                    }
                }
                ans += max(0ll, pos - 2);
            }
            if (n >= 4) {
                ll S = a[0] + a[1] + a[2];
                ll T = max(a[3], 2 * a[0]);
                if (S > T) ans++;
            }
        }

        for (int i = 1; i <= n - 3; ++i)
            ans += calc(i + 1, n - 1, max(a[0], 2 * a[i]) - a[i]);
        cout << ans << '\n';
    }

    return 0;
}