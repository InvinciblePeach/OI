#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 5010;
int T, n, a[MAXN];
ll ans;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        cin >> n;
        ans = 0;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1, l = n + 1, r = j; j <= n; j++) {
                l = max(l, j + 1);
                while (l > j + 1 && a[i] + a[j] + a[l - 1] > a[n]) l--;
                r = max(r, j + 1);
                while (r <= n && a[r] < a[i] + a[j]) r++;
                ans += max(0, r - l);
            }
        }
        cout << ans << '\n';
    }

    return 0;
}