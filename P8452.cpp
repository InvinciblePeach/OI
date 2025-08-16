#include <bits/stdc++.h>

using namespace std;

int S, n, m, T;

int main() {
    cin >> S >> T;
    while (T --> 0) {
        cin >> n >> m;
        int ans = 0;
        for (int i = 1; i <= n; i ++) {
            if (i % 2) {
                ans += m / 2;
            } else {
                ans += m;
            }
        }
        int x = (n % 2 == 0 ? n - 1 : n);
        int y = m;
        cout << ans << ' ' << sqrtl((x - 1) * (x - 1) + (y - 1) * (y - 1)) << endl;
    }
    return 0;
}