#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int n, m, cnt, fa[MAXN], col[MAXN];
vector<int> g[MAXN];
queue<int> q;

int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }

int merge(int x, int y) {
    x = get(x), y = get(y);
    if (g[x].size() < g[y].size()) swap(x, y);
    for (auto v : g[y])
        g[x].emplace_back(v);
    g[y].clear();
    fa[y] = x;
    return x;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        g[u].emplace_back(v);
    }
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        if (g[i].size() > 1) q.emplace(i);
    }
    while (!q.empty()) {
        int u = q.front(), nw = g[u][0];
        q.pop();
        for (int i = 1; i < g[u].size(); i++) {
            int v = g[u][i];
            if (get(v) ^ get(nw)) nw = merge(v, nw);
        }
        g[u].clear(), g[u].emplace_back(nw);
        if (g[get(nw)].size() > 1) q.emplace(get(nw));
    }
    for (int i = 1; i <= n; i++) {
        if (!col[get(i)]) col[get(i)] = ++cnt;
        cout << col[get(i)] << "\n";
    }

    return 0;
}