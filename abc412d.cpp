#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10;
int n, m, f[1 << MAXN], dp[1 << MAXN];
bitset<MAXN> g[MAXN];


int main() {
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        g[u][v] = g[v][u] = true;
    }
    memset(f, -1, sizeof(f));
    for (int st = 0; st < (1 << n); st++) {
        int k = __builtin_popcount(st);
        if (k < 3) continue;
        vector<int> tmp;
        for (int i = 1; i <= n; i++)
            if (st >> (i - 1) & 1) tmp.push_back(i);
        do {
            int cnt = 0;
            for (int i = 0; i < tmp.size(); i++) {
                int u = tmp[i], v = tmp[(i + 1) % tmp.size()];
                if (g[u][v]) cnt++;
            }
            f[st] = max(f[st], cnt);
        } while (next_permutation(tmp.begin() + 1, tmp.end()));
    }
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    for (int st = 1; st < (1 << n); st++)
        for (int i = st; i; i = (i - 1) & st)
            if (~f[i]) dp[st] = max(dp[st], dp[st ^ i] + f[i]);
    cout << m + n - 2 * dp[(1 << n) - 1] << "\n";
    return 0;
}