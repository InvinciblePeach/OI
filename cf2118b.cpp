#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int T, n;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        cin >> n;
        cout << 2 * n - 1 << '\n';
        cout << "1 1 " << n << '\n';
        for (int i = 2; i <= n; i++) {
            cout << i << " 1 " << i - 1 << '\n';
            cout << i << ' ' << i << ' ' << n << '\n';
        }
    }

    return 0;
}