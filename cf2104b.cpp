#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int t, n, a[MAXN], mx[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> t;
    while (t --> 0) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            mx[i] = max(mx[i - 1], a[i]);
        }
        for (int k = n, sum = 0; k; k--) {
            sum += a[k];
            int lst = a[k];
            if (mx[k - 1] > lst)
                cout << sum - lst + mx[k - 1] << ' ';
            else
                cout << sum << ' ';
        }
        cout << '\n';
    }

    return 0;
}