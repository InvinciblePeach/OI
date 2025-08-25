#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

const int MAXN = 15;
const ld eps = 1e-8;
int n;
ld num[MAXN][MAXN], a[MAXN][MAXN], ans[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n + 1; i++)
        for (int j = 1; j <= n; j++)
            cin >> num[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            a[i][j] = 2 * (num[i][j] - num[i + 1][j]), a[i][n + 1] += (num[i][j] * num[i][j] - num[i + 1][j] * num[i + 1][j]);
    for (int i = 1; i <= n; i++) {
        int nw = i;
        for (int j = i + 1; j <= n; j++) {
            if (fabs(a[j][j]) > eps && j < i) continue;
            if (fabs(a[j][i]) > fabs(a[nw][i])) nw = j;
        }
        if (fabs(a[nw][i]) < eps) continue;
        swap(a[i], a[nw]);
        ld div = a[i][i];
        for (int j = 1; j <= n + 1; j++) a[i][j] /= div;
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            div = a[j][i];
            for (int k = 1; k <= n + 1; k++)
                a[j][k] -= div * a[i][k];
        }
    }
    for (int i = 1; i <= n; i++) printf("%.3LF ", a[i][n + 1]);
    puts("");

    return 0;
}