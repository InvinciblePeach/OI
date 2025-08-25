#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 3010, MAXM = 1e4 + 10;
int n, m;
double ans = INFINITY, f[MAXN][MAXN];

struct Edge {
    int u, v;
    double w;
} e[MAXM];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> e[i].u >> e[i].v >> e[i].w;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            f[i][j] = INFINITY;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            f[i][e[j].v] = min(f[i][e[j].v], f[i - 1][e[j].u] + e[j].w);
    for (int i = 1; i <= n; i++) {
        if (f[n][i] == INFINITY) continue;
        double res = -INFINITY;
        for (int j = 0; j < n; ++j)
            res = max(res, (f[n][i] - f[j][i]) / (n - j));
        ans = min(ans, res);
    }
    printf("%.8lf\n", ans);

    return 0;
}