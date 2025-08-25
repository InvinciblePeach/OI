#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 1e6 + 10, MAXV = 2010;
int n, m, s, f[40][MAXV], g[40][MAXV];
vector<int> val[40], k[40];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    while (cin >> n >> m && ~n && ~m) {
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
        for (int i = 0; i < 40; i++) val[i].clear(), k[i].clear();
        for (int i = 1, w, v; i <= n; i++) {
            cin >> w >> v;
            int t = 0;
            while (!((w >> t) & 1)) t++;
            val[t].emplace_back(v);
            k[t].emplace_back(w >> t);
        }
        s = 0;
        while (m >> s) s++;
        for (int i = 0; i < s; i++) {
            if (k[i].empty()) continue;
            for  (int j = 0; j < k[i].size(); j++)
                for (int p = 1000; p >= k[i][j]; p--)
                    g[i][p] = max(g[i][p], g[i][p - k[i][j]] + val[i][j]);
        }
        for (int i = 0; i < s; i++)
            for (int j = 1000; ~j; j--)
                for (int p = 0; p <= j; p++)
                    if (!i) f[i][j] = max(f[i][j], g[i][p]);
                    else f[i][j] = max(f[i][j], f[i - 1][(j - p) * 2 + (m >> (i - 1) & 1)] + g[i][p]);
        cout << f[s - 1][1] << '\n';
    }

    return 0;
}