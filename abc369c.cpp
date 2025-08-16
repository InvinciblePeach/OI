#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 2e5 + 10;
int n, m, ans, mx, b[MAXN], w[MAXN], s[MAXN], t[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= m; i++) cin >> w[i];
    sort(b + 1, b + 1 + n, greater<>()),
    sort(w + 1, w + 1 + m, greater<>());
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + b[i];
    for (int i = 1; i <= m; i++) t[i] = t[i - 1] + w[i];
    for (int i = 1; i <= n; i++)
        ans = max(ans, s[i] + (mx = max(mx, t[i])));
    cout << ans << '\n';

    return 0;
}