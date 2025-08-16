#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int T, a, x, y;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        cin >> a >> x >> y;
        if ((x <= a && a <= y) || (y <= a && a <= x)) cout << "NO\n";
        else cout << "YES\n";
    }

    return 0;
}