#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int n, t, ans;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> t;
    while (t --> 0) {
        cin >> n;
        ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += abs((n - i + 1) - i);
        }
        cout << (ans >> 1) + 1 << '\n';
    }

    return 0;
}