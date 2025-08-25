#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e3 + 10;
int n, b, st[MAXN], tp, tot, id[MAXN], blk[MAXN];
vector<int> g[MAXN];

void dfs(int u, int fa) {
    int nw = tp;
    for (auto v : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
        if (tp - nw >= b) {
            id[++tot] = u;
            while (tp > nw) blk[st[tp--]] = tot;
        }
    }
    st[++tp] = u;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> b;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs(1, 0);
    if (!tot) id[++tot] = 1;
    while (tp) blk[st[tp--]] = tot;
    cout << tot << '\n';
    for (int i = 1; i <= n; i++) cout << blk[i] << ' ';
    cout << '\n';
    for (int i = 1; i <= tot; i++) cout << id[i] << ' ';
    cout << '\n';

    return 0;
}