#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

int T, a, b, x, y;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        cin >> a >> b >> x >> y;
        if (a > b) {
            if ((a ^ 1) == b) cout << y << '\n';
            else cout << "-1\n";
            continue;
        }
        int ans = 0;
        while (a < b) {
            if (a & 1) { ans += x, a++; }
            else {
                if (x < y) ans += x, a++;
                else ans += y, a++;
            }
        }
        cout << ans << '\n';
    }

    return 0;
}