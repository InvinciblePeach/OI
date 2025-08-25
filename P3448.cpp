#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 50, mod = 1e6;
int a, b, c, d, ans, f[2][MAXN][MAXN][MAXN][4][4];

bool check(int x, int y, int z) {
    if (x == -1 || y == -1) return true;
    int a = (x & 1) + (y & 1) + (z & 1), b = (x < 2) + (y < 2) + (z < 2);
    return a && a < 3 && b && b < 3;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> a >> b >> c >> d, f[0][0][0][0][0][0] = 1;
    for (int nw = 0, i = 0; nw <= a; nw++, i ^= 1) {
        memset(f[i ^ 1], 0, sizeof(f));
        for (int j = 0; j <= b; j++)
            for (int k = 0; k <= c; k++)
                for (int l = 0, s = nw + j + k; l <= d; l++, s++)
                    for (int x = 0; x < 4; x++)
                        for (int y = 0, v; y < 4; y++)
                            if (v = f[i][j][k][l][x][y]) {
                                int q2 = s <= 1 ? -1 : x, q1 = !s ? -1 : y;
                                if (nw < a && check(q2, q1, 0)) (f[i ^ 1][j][k][l][y][0] += v) %= mod;
                                if (j < b && check(q2, q1, 1)) (f[i][j + 1][k][l][y][1] += v) %= mod;
                                if (k < c && check(q2, q1, 2)) (f[i][j][k + 1][l][y][2] += v) %= mod;
                                if (l < d && check(q2, q1, 3)) (f[i][j][k][l + 1][y][3] += v) %= mod;
                            }
    }
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            (ans += f[a & 1][b][c][d][i][j]) %= mod;
    cout << ans << '\n';
    return 0;
}
