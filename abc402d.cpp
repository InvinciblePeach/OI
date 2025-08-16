#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 1e6 + 10;
int n, m, ans, cnt[MAXN];


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    ans = m * (m - 1) >> 1;
    for (int i = 1, a, b; i <= m; i++) {
        cin >> a >> b;
        cnt[(a + b) % n]++;
    }
    for (int i = 0; i <= n; i++)
        ans -= cnt[i] * (cnt[i] - 1) >> 1;
    cout << ans << '\n';

    return 0;
}