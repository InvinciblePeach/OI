#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 510;
int T, n, m, k, sum[MAXN][MAXN], ans;
char g[MAXN][MAXN];
bool flag;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        cin >> n >> m >> k;
        ans = INT_MAX, flag = false;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> g[i][j];
                sum[i][j] = sum[i][j - 1] + (g[i][j] == 'g');
                if (g[i][j] == '.') flag = true;
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                sum[i][j] += sum[i - 1][j];
            }
        }
        if (!flag) {
            cout << "0\n";
            continue;
        }
        k--;
        auto calc = [=](int a, int b, int c, int d) {
            a = max(a, 1), b = max(b, 1), c = min(c, n), d = min(d, m);
            return sum[c][d] - sum[c][b - 1] - sum[a - 1][d] + sum[a - 1][b - 1];
        };
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (g[i][j] == '.')
                ans = min(ans, calc(i - k, j - k, i + k, j + k));
            }
        }
        cout << sum[n][m] - ans << '\n';
    }

    return 0;
}