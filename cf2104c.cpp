#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 10;
int t, n;
unordered_set<int> a, b;

bool finda(int x) {
    return a.find(x) != a.end();
}

bool findb(int x) {
    return b.find(x) != b.end();
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> t;
    while (t --> 0) {
        cin >> n;
        a.clear(), b.clear();
        for (int i = 1; i <= n; i++) {
            static char c;
            cin >> c;
            if (c == 'A') a.emplace(i);
            if (c == 'B') b.emplace(i);
        }

        if (findb(1) && findb(n)) {
            cout << "Bob\n";
        } else if (findb(1) && finda(n)) {
            if (finda(n - 1)) cout << "Alice\n";
            else cout << "Bob\n";
        } else if (finda(1) && findb(n)) {
            if (b.size() > 1) cout << "Bob\n";
            else cout << "Alice\n";
        } else {
            cout << "Alice\n";
        }

    }

    return 0;
}