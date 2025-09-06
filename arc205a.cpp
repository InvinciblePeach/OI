#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 510;
int n, q, sum[MAXN][MAXN];
char g[MAXN][MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> g[i][j];
    // cerr << "done\n";
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) sum[i][j] = (g[i][j] + g[i - 1][j] + g[i][j - 1] + g[i - 1][j - 1] == ('.' << 2));
    // for (int i = 1; i <= n; i++)
    //     for (int j = 1; j <= n; j++) cerr << sum[i][j] << " \n"[j == n];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) sum[i][j] += sum[i][j - 1];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) sum[i][j] += sum[i - 1][j];
    while (q-- > 0) {
        static int u, d, l, r;
        cin >> u >> d >> l >> r;
        if (d - u < 1 || r - l < 1) {
            cout << "0\n";
            continue;
        }
        auto calc = [=](int a, int b, int x, int y) {
            return sum[x][y] - sum[a - 1][y] - sum[x][b - 1] + sum[a - 1][b - 1];
        };
        cout << calc(u + 1, l + 1, d, r) << '\n';
    }

    return 0;
}