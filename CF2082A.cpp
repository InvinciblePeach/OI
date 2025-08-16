#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 110;
int t, n, m, cnt;
bitset<MAXN> a[MAXN], row, col;

void solve() {
    cnt = 0;
    row.reset(), col.reset();
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        static char x;
        for (int j = 1; j <= m; j++) {
            cin >> x, x -= '0';
            a[i][j] = x, row[i] = row[i] ^ x, col[j] = col[j] ^ x;
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (row[i] && col[j]) row[i] = col[j] = 0, cnt++;
    for (int i = 1; i <= n; i++) {
        if (row[i]) row[i] = 0, cnt++;
    }
    for (int i = 1; i <= m; i++) {
        if (col[i]) col[i] = 0, cnt++;
    }
    cout << cnt << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> t;
    while (t-- > 0)
        solve();

    return 0;
}