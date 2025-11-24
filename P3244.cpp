#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e5 + 10, mod = 1e9 + 7;
int n, m, x, y, tot = 1, deg[MAXN], in[MAXN], dp[MAXN];
bitset<MAXN> vis;
vector<int> g[MAXN];

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        b >>= 1, (a *= a) %= mod;
    }
    return res;
}

int inv(int x) { return qpow(x, mod - 2); }

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> x >> y, deg[y]++;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        deg[v]++, in[v]++, g[u].emplace_back(v);
    }
    for (int i = 2; i <= n; i++) (tot *= deg[i]) %= mod;

    if (y == 1) return cout << tot << '\n', 0;
    dp[y] = tot;
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (!in[i]) q.emplace(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        (dp[u] *= inv(deg[u])) %= mod;
        for (auto v : g[u]) {
            (dp[v] += dp[u]) %= mod;
            if (!--in[v]) q.emplace(v);
        }
    }
    cout << ((tot - dp[x]) % mod + mod) % mod << '\n';

    return 0;
}