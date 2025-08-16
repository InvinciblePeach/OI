#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 210;
int q, st[MAXN], tp = 100;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> q;
    while (q --> 0) {
        static int c, x;
        cin >> c;
        if (c == 1) {
            cin >> x;
            st[++tp] = x;
        } else {
            cout << st[tp--] << '\n';
        }
    }

    return 0;
}