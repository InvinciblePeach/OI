#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int n, m, q;
unordered_set<int> a[MAXN];
bitset<MAXN> all;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> q;
    while (q --> 0) {
        static int opt, x, y;
        cin >> opt >> x;
        if (opt == 1) {
            cin >> y;
            a[x].emplace(y);
        } else if (opt == 2) {
            all[x] = 1;
        } else {
            cin >> y;
            if (all[x] || a[x].find(y) != a[x].end()) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }

    return 0;
}