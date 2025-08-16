#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;
int T, n;
string s;

void solve() {
    cin >> n;
    cin >> s;
    s = ' ' + s;
    int id = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i] > s[i + 1]) {
            id = i;
            break;
        }
    }
    if (!id) {
        for (int i = 1; i <= n; i++) cout << s[i];
        cout << '\n';
        return;

    }
    auto tmp = s[id];
    int r = n;
    for (int i = id; i <= n; i++) {
        if (s[i] > s[id]) {
            r = i - 1;
            break;
        }
    }
    for (int i = id; i < r; i++) {
        s[i] = s[i + 1];
    }
    s[r] = tmp;
        for (int i = 1; i <= n; i++) cout << s[i];
        cout << '\n';
        return;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) solve();

    return 0;
}