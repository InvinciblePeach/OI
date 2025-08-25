#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 110;
int n, ans;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1, a; i <= n; i++) {
        cin >> a;
        if (i & 1) ans += a;
    }
    cout << ans << '\n';

    return 0;
}