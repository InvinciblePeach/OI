#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 2e5 + 10;
int n, m, p, d[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    p = n * (n - 1) >> 1;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        d[u] ^= 1, d[v] ^= 1;
    }
    if (n < 3) return cout << m << '\n', 0;
    auto nw = (n - 1) & 1;
    int tmp = 0;
    for (int i = 1; i <= n; i++)
        if (d[i] ^ nw) tmp++;
    cout << (p - (tmp >> 1)) << '\n';

    return 0;
}
