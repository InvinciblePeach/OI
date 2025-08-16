#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXV = (1 << 10) - 1;
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
int n = rnd() % 999 + 2, m = rnd() % (n + 1);

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cout << n << ' ' << m << '\n';
    for (int i = 1; i <= m; i++) {
        int u = rnd() % n + 1, v = rnd() % n + 1, w = rnd() & MAXV;
        cout << u << ' ' << v << ' ' << w << '\n';
    }

    return 0;
}