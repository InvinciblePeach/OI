#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 110;
int n, p[MAXN][MAXN], r[MAXN][MAXN], d[MAXN][MAXN], f[MAXN][MAXN][2], dis[MAXN][MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> p[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < n; j++)
            cin >> r[i][j];
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= n; j++)
            cin >> d[i][j];
    memset(f, 0x3f, sizeof(f));
    f[1][1][0] = f[1][1][1] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            memset(dis, 0x3f, sizeof(dis));
            dis[i][j] = 0;
            for (int x = i; x; x--) {
                for (int y = j; y; y--) {
                    if (y < j) dis[x][y] = min(dis[x][y], r[x][y] + dis[x][y + 1]);
                    if (x < i) dis[x][y] = min(dis[x][y], d[x][y] + dis[x + 1][y]);
                    int mx = max(0ll, (dis[x][y] - f[x][y][1] - 1 + p[x][y]) / p[x][y]),
                        tmp1 = f[x][y][0] + mx + i + j - x - y, tmp2 = f[x][y][1] + mx * p[x][y] - dis[x][y];
                    if (tmp1 < f[i][j][0] || (tmp1 == f[i][j][0] && tmp2 > f[i][j][1])) {
                        f[i][j][0] = tmp1;
                        f[i][j][1] = tmp2;
                    }
                }
            }
        }
    }
    cout << f[n][n][0] << '\n';
}