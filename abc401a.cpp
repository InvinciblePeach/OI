#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 110;
int n, a[MAXN], k, ans;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> k;
    for (int i = 1; i <= n; i++) ans += (a[i] >= k);
    cout << ans << '\n';

    return 0;
}