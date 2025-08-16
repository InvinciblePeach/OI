#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 10, mod = 12345678;
int n, m, ans, dp[30][1 << 10], f[1 << 10];
bitset<MAXN> vis[MAXN], g[MAXN];
int dx[]{-1, 0, 1, 0, -1, 1, -1, 1};
int dy[]{0, -1, 0, 1, -1, -1, 1, 1};

struct Node {
    int x, y;
} pnt[MAXN];

int calc() {
    int cnt = 0;
    memset(dp, 0, sizeof(dp));
    memset(vis, 0, sizeof(vis));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (g[i][j]) pnt[++cnt] = {i, j};
    for (int i = 0, sum; i < (1 << cnt); i++) {
        memset(vis, 0, sizeof(vis)), sum = 0;
        for (int j = 1; j <= cnt; j++) {
            if (i >> (j - 1) & 1) continue;
            if (!vis[pnt[j].x][pnt[j].y]) vis[pnt[j].x][pnt[j].y] = 1, sum++;
            for (int k = 0, nx, ny; k < 8; k++) {
                nx = pnt[j].x + dx[k], ny = pnt[j].y + dy[k];
                if (nx > 0 && nx <= n && ny > 0 && ny <= m && !vis[nx][ny]) vis[nx][ny] = 1, sum++;
            }
        }
        f[i] = n * m - sum;
    }
    for (int i = 1; i <= n * m; i++) {
        for (int j = 0; j < (1 << cnt); j++) {
            (dp[i][j] += dp[i - 1][j] * max(f[j] - i + 1, 0) % mod) %= mod;
            for (int k = 1; k <= cnt; k++)
                if (!(j & (1 << (k - 1)))) (dp[i][j | 1 << (k - 1)] += dp[i - 1][j]) %= mod;
        }
    }
    return dp[n * m][(1 << cnt) - 1];
}

void dfs(int x, int y, int op) {
    if (x > n) return (ans += op * calc()) %= mod, void();
    if (y > m) return dfs(x + 1, 1, op), void();
    dfs(x, y + 1, op);
    if (!g[x][y]) {
        bool flag = false;
        for (int k = 0, nx, ny; k < 8; k++) {
            nx = x + dx[k], ny = y + dy[k];
            if (g[nx][ny]) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            g[x][y] = 1;
            dfs(x, y + 1, -op);
            g[x][y] = 0;
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        char c;
        for (int j = 1; j <= m; j++) {
            cin >> c;
            g[i][j] = (c == 'X');
        }
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (g[i][j] && (g[i - 1][j] || g[i][j - 1])) return cout << "0\n", 0;
    dfs(1, 1, 1);
    cout << (ans + mod) % mod << '\n';

    return 0;
}