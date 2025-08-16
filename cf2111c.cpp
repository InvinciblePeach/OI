#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 5e5 + 10;
int T, n, a[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        cin >> n;
        int mn = LLONG_MAX;
        a[0] = a[n + 1] = -1;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 2, len = 1; i <= n + 1; i++) {
            if (a[i] == a[i - 1]) len++;
            else {
                mn = min(mn, (n - len) * a[i - 1]);
                len = 1;
            }
        }
        cout << mn << '\n';
    }

    return 0;
}