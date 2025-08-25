#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 110;
int n, m, a[MAXN][MAXN], sum[MAXN][MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            sum[i][j] = sum[i - 1][j] + a[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            sum[i][j] += sum[i][j - 1];

    auto calc = [=](int a1, int b1, int a2, int b2) {
        return sum[a2][b2] - sum[a1 - 1][b2] - sum[a2][b1 - 1] + sum[a1 - 1][b1 - 1];
    };

    n++, m++;
    int ans = LLONG_MIN;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int x = 0; x <= min(i - 1, n - i); x++)
                for (int y = 0; y <= min(j - 1, m - j); y++)
                    ans = max(ans, calc(i - x, j - y, i + x, j + y));
    cout << ans << "\n";
    return 0;
}