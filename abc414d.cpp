#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 5e5 + 10;
int n, m, x[MAXN], d[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> x[i];
    sort(x + 1, x + 1 + n);

    if (m >= n) {
        cout << 0 << '\n';
        return 0;
    }

    for (int i = 1; i < n; i++) {
        d[i] = x[i + 1] - x[i];
    }

    int sum = x[n] - x[1];

    sort(d + 1, d + n, greater<>());
    for (int i = 1; i <= m - 1; i++)
        sum -= d[i];
    cout << sum << "\n";
    return 0;
}
