#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 5e5 + 10;
int T, n, m, cnt, hd[MAXN];

struct Edge {
    int nxt, v, w;
} g[MAXN];

void add(int u, int v, int w) {
    g[++cnt] = {hd[u], v, w};
    hd[u] = cnt;
}

void solve() {
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        add()
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) solve();

    return 0;
}