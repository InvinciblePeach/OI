#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2010;
int n, x, ans;
bool flag = true;
bitset<MAXN> mat[MAXN];

void gauss() {
    for (int i = 1; i <= n; i++) {
        int nw = i;
        for (int j = i + 1; j <= n; j++)
            if (mat[j][i]) nw = j;
        swap(mat[i], mat[nw]);
        if (!mat[i][i]) continue;
        for (int j = 1; j <= n; j++) {
            if ((i ^ j) && mat[j][i]) mat[j] ^= mat[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!mat[i][i] && mat[i][n + 1]) flag = false;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1, m, k; i <= n; i++) {
        cin >> m;
        if (m & 1) mat[i][n + 1] = mat[i][i] = 1;
        while (m-- > 0) cin >> k, mat[i][k] = 1;
    }
    gauss();
    if (!flag) {
        cout << "Impossible\n";
        return 0;
    }
    for (int i = 1; i <= n; i++)
        if (mat[i][n + 1]) ans++;
    cout << ans << '\n';
    for (int i = 1; i <= n; i++) {
        if (mat[i][n + 1]) cout << i << ' ';
    }
    cout << '\n';
    return 0;
}