#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int T, n, k;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        cin >> n >> k;
        for (int i = 1; i <= n - k; i++) cout << '0';
        for (int i = 1; i <= k; i++) cout << '1';
        cout << '\n';
    }

    return 0;
}