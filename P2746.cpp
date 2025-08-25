#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 110;
int n, m, tot, cnt;
int top, st[MAXN], id[MAXN], low[MAXN], scc[MAXN];
int in[MAXN], out[MAXN];
bitset<MAXN> vis;
vector<int> g[MAXN];

void tarjan(int u) {
    vis[u] = 1;
    id[u] = low[u] = ++tot;
    st[++top] = u;
    for (auto v : g[u]) {
        if (!id[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v]) low[u] = min(low[u], id[v]);
    }
    if (id[u] == low[u]) {
        scc[u] = ++cnt, vis[u] = 0;
        while (st[top] != u)
            scc[st[top]] = cnt, vis[st[top]] = 0, top--;
        top--;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1, k; i <= n; i++) {
        while (cin >> k && k)
            g[i].emplace_back(k);
    }

    for (int i = 1; i <= n; i++)
        if (!id[i]) tarjan(i);
    for (int u = 1; u <= n; u++)
        for (auto v : g[u])
            if (scc[u] != scc[v]) out[scc[u]]++, in[scc[v]]++;
    int ans1 = 0, ans2 = 0;
    for (int i = 1; i <= cnt; i++) {
        if (in[i] == 0) ans1++;
        if (out[i] == 0) ans2++;
    }
    cout << ans1 << '\n';
    if (cnt == 1) cout << "0\n";
    else cout << max(ans1, ans2) << '\n';

    return 0;
}