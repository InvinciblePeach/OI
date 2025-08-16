#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;
int n, a, b, ans;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a >> b;
        if (b > a) ans++;
    }
    cout << ans << '\n';

    return 0;
}