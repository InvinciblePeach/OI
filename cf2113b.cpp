#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int T, w, h, a, b;

namespace tjy {
    void solve() {
        cin >> w >> h >> a >> b;
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if ((abs(x1 - x2) % a || abs(x1 - x2) == 0) && (abs(y1 - y2) % b || abs(y1 - y2) == 0))
        return cout << "No\n", void();
        cout << "Yes\n";
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        tjy::solve();
    }

    return 0;
}