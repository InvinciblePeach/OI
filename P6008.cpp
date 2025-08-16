#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 1010, mod = 1e9 + 7;
int n, m, fa[MAXN * MAXN], dp[MAXN * MAXN], ans = 1;
bitset<MAXN * MAXN> vis;
char g[MAXN][MAXN];
int dx[] = {0, 0, 1};
int dy[] = {-1, 1, 0};

int calc(int a, int b) { return (a - 1) * m + b; }

int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }

void merge(int x, int y) {
    auto [fax, fay] = pair<int, int>(get(x), get(y));
    if (fax ^ fay) fa[fay] = fax, (dp[fax] *= dp[fay]) %= mod;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> g[i][j], fa[calc(i, j)] = calc(i, j), dp[calc(i, j)] = 1;

    for (int i = n - 1; i > 1; i--) {
        for (int j = 2; j < m; j++) {
            if (g[i][j] == '#') continue;
            for (int k = 0; k < 3; k++) {
                auto [nx, ny] = pair<int, int>(i + dx[k], j + dy[k]);
                if (g[nx][ny] ^ '#') merge(calc(i, j), calc(nx, ny));
            }
        }
        for (int j = 2; j < m; j++) {
            if (g[i][j] == '#') continue;
            int fa = get(calc(i, j));
            if (vis[fa]) continue;
            vis[fa] = 1, (dp[fa] += 1) %= mod;
        }
    }
    for (int i = 2; i < n; i++) {
        for (int j = 2; j < m; j++) {
            if (g[i][j] == '#') continue;
            if (get(calc(i, j)) == calc(i, j)) (ans *= dp[calc(i, j)]) %= mod;
        }
    }
    cout << ans << '\n';

    return 0;
}