#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 1e5 + 10;
int n, l, r, ans;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> l >> r;
    for (int i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        if ((x <= l && y >= r)) ans++;
    }
    cout << ans << '\n';

    return 0;
}