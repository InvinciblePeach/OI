#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 70;
int n, m, tot, cnt, top, id[MAXN], low[MAXN], st[MAXN], scc[MAXN];
bitset<MAXN> vis;
vector<int> g[MAXN];

void tarjan(int u) {
    id[u] = low[u] = ++tot;
    st[++top] = u, vis[u] = 1;
    for (auto v : g[u]) {
        if (!id[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v]) low[u] = min(low[u], id[v]);
    }
    if (id[u] == low[u]) {
        vis[u] = 0, scc[u] = ++cnt;
        while (st[top] != u)
            vis[st[top]] = 0, scc[st[top]] = cnt, top--;
        top--;
    }
}

void solve() {
    tot = cnt = top = 0;
    memset(id, 0, sizeof(id));
    memset(low, 0, sizeof(low));
    memset(scc, 0, sizeof(scc));
    for (int i = 1; i <= (2 * n); i++) g[i].clear();
    for (int i = 1; i <= m; i++) {
        static int a, b;
        static char x, y;
        cin >> a >> x >> b >> y;
        a++, b++;
        if (x == 'w' && y == 'h') {
            g[a].emplace_back(b);
            g[b + n].emplace_back(a + n);
        } else if (x == 'h' && y == 'w') {
            g[a + n].emplace_back(b + n);
            g[b].emplace_back(a);
        } else if (x == 'w' && y == 'w') {
            g[a].emplace_back(b + n);
            g[b].emplace_back(a + n);
        } else if (x == 'h' && y == 'h') {
            g[a + n].emplace_back(b);
            g[b + n].emplace_back(a);
        }
    }
    g[1].emplace_back(1 + n);
    for (int i = 1; i <= (2 * n); i++)
        if (!id[i]) tarjan(i);
    for (int i = 1; i <= n; i++)
        if (scc[i] == scc[i + n]) return cout << "bad luck\n", void();
    for (int i = 2; i <= n; i++) {
        if (scc[i] > scc[i + n]) cout << i - 1 << "w ";
        else cout << i - 1 << "h ";
    }
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    while (cin >> n >> m && n) solve();
    return 0;
}