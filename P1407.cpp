#include <bits/stdc++.h>

using namespace std;

const int MAXN = 8020;
int n, m, cnt, tot;
int st[MAXN], top, dfn[MAXN], low[MAXN], scc[MAXN], siz[MAXN];
bitset<MAXN> vis;
unordered_map<string, int> mp;
vector<int> graph[MAXN];

void tarjan(int u) {
    vis[u] = 1;
    dfn[u] = low[u] = ++cnt;
    st[++top] = u;
    for (auto v : graph[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        scc[u] = ++tot, vis[u] = 0, siz[cnt]++;
        while (st[top] != u)
            vis[st[top]] = 0, siz[scc[st[top]] = tot]++, top--;
        top--;
    }
}

signed main() {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        string g, b;
        cin >> g >> b;
        mp[g] = i;
        mp[b] = i + n;
        graph[i].emplace_back(i + n);
    }
    cin >> m;
    for (int i = 1; i <= m; i ++) {
        string g, b;
        cin >> g >> b;
        graph[mp[b]].emplace_back(mp[g]);
    }
    for (int i = 1; i <= (n << 1); i ++)
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n; i ++) {
        if (scc[i] == scc[i + n]) cout << "Unsafe" << endl;
        else cout << "Safe" << endl;
    }
    return 0;
}