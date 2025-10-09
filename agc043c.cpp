#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e5 + 10, mod = 998244353, base = 1000000000000000000ll % mod;
int n, m, len = 1, sg[3][MAXN], f[3][MAXN], pw[MAXN];
vector<int> g[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    while (len < n) len <<= 1;

    pw[0] = 1;
    for (int i = 1; i <= n; i++) pw[i] = pw[i - 1] * base % mod;
    for (int t = 0; t < 3; t++) {
        cin >> m;
        for (int i = 1; i <= n; i++) g[i].clear();
        for (int i = 1, u, v; i <= m; i++) {
            cin >> u >> v;
            if (u > v) swap(u, v);
            g[u].emplace_back(v);
        }
        for (int i = n; i; i--) {
            set<int> mex;
            for (auto j : g[i]) mex.insert(sg[t][j]);
            while (mex.count(sg[t][i])) sg[t][i]++;
        }
        for (int i = 1; i <= n; i++) (f[t][sg[t][i]] += pw[i]) %= mod;
    }
    int ans = 0;
    for (int i = 0; i <= 500; i++)
        for (int j = 0; j <= 500; j++) (ans += f[0][i] * f[1][j] % mod * f[2][i ^ j]) %= mod;
    cout << ans << '\n';
    return 0;
}