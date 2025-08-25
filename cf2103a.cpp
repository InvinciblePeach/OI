#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 110;
int T, n, m;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        cin >> n;
        set<int> s;
        s.clear();
        for (int i = 1, x; i <= n; i++) {
            cin >> x;
            s.emplace(x);
        }
        cout << s.size() << '\n';
    }

    return 0;
}