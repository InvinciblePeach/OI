#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 2e5 + 10, INF = 0x3f3f3f3f3f3f3f3f;
int n, f[MAXN], sum, a[2][MAXN], s[2][MAXN], t[MAXN];
map<int, int> mp;

int &g(int i, int j) {
    if (mp.find(j - s[0][i]) == mp.end()) mp[j - s[0][i]] = -INF;
    return mp[j - s[0][i]];
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 0; i < 2; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j], sum += a[i][j], a[i][j] *= (n << 1);
    for (int i = 0; i < 2; i++)
        for (int j = 1; j <= n; j++) a[i][j] -= sum, s[i][j] = s[i][j - 1] + a[i][j];
    for (int i = 1; i <= n; i++) t[i] = s[0][i] + s[1][i];
    f[0] = 0;
    g(0, 0) = 0;
    for (int i = 1; i <= n; i++) {
        f[i] = max({f[i - 1], g(i - 1, 0), g(i - 1, t[i - 1])}) + !t[i];
        g(i, 0)++, g(i, t[i])++;
        g(i, t[i - 1] + a[0][i]) = max(g(i, t[i - 1] + a[0][i]), f[i - 1] + !(t[i - 1] + a[0][i]) + !a[1][i]);
        g(i, a[0][i]) = max(g(i, a[0][i]), f[i - 1] + !(t[i - 1] + a[1][i]) + !a[0][i]);
    }
    cout << max(f[n], g(n, 0)) << '\n';

    return 0;
}