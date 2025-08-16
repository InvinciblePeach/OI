#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

int t, n, x;

void solve() {
    cin >> n >> x;
    if (n == 1) {
        return cout << (x ? x : -1) << '\n', void();
    } else if (n == 2) {
        if (x == 0)
            return cout << 2 << '\n', void();
        else if (x == 1)
            return cout << 5 << '\n', void();
        else {
            int tmp = x, cnt = 0;
            while (tmp) {
                if (tmp & 1) cnt++;
                tmp >>= 1;
            }
            if (cnt > 1)
                cout << x << '\n';
            else {
                cout << x + 2 << '\n';
            }
        }
    } else if (x == 0) {
        if (n & 1)
            cout << n + 3 << '\n';
        else
            cout << n << '\n';
    } else if (x == 1) {
        if (n & 1) cout << n << '\n';
        else cout << n + 3 << '\n';
    } else {
        int tmp = x, cnt = 0;
        while (tmp) {
            if (tmp & 1) cnt++;
            tmp >>= 1;
        }
        if (cnt >= n)
            cout << x << '\n';
        else {
            if ((n - cnt) & 1)
                cout << x + (n - cnt) + 1 << '\n';
            else
                cout << x + (n - cnt) << '\n';
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> t;
    while (t --> 0) {
        solve();
    }

    return 0;
}