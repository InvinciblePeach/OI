#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int n, m, ans, fa[MAXN], siz[MAXN];
vector<int> g[MAXN];
bitset<MAXN> vis;

int get(int x) {
    if (fa[x] == x) return x;
    return fa[x] = get(fa[x]);
}

void merge(int a, int b) {
    int p = get(a), q = get(b);
    if (p == q) return;
    siz[q] += siz[p];
    fa[p] = q;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    for (int k = 1; k <= n; k++) {
        if (vis[k]) ans--;
        for (auto v : g[k])
            if (v <= k) merge(v, k);
        for (auto v : g[k]) {
            if (v > k && !vis[v]) vis[v] = 1, ans++;
        }
        if (siz[get(k)] < k) {
            cout << -1 << '\n';
        } else {
            cout << ans << '\n';
        }
    }

    return 0;
}