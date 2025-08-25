#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int n, m, cnt, tot, dfn[MAXN], low[MAXN], siz[MAXN], w[MAXN];
int st[MAXN], top, ans;
vector<int> g[MAXN], t[MAXN];

void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++tot;
    w[st[++top] = u] = -1;
    for (auto v : g[u]) {
        if (v == fa) continue;
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                cnt++;
                do t[st[top]].emplace_back(cnt), t[cnt].emplace_back(st[top]), w[cnt]++;
                while (st[top--] ^ v);
                t[u].emplace_back(cnt), t[cnt].emplace_back(u), w[cnt]++;
            }
        } else low[u] = min(low[u], dfn[v]);
    }
}

void dfs(int u, int fa) {
    siz[u] = u <= n;
    for (auto v : t[u]) {
        if (v == fa) continue;
        dfs(v, u);
        ans += 2 * siz[u] * siz[v] * w[u];
        siz[u] += siz[v];
    }
    ans += 2 * siz[u] * (tot - siz[u]) * w[u];
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        g[u].emplace_back(v), g[v].emplace_back(u);
    }
    cnt = n;
    for (int i = 1; i <= n; i++) {
        if (dfn[i]) continue;
        tot = 0;
        tarjan(i, 0);
        dfs(i, 0);
    }
    cout << ans << '\n';

    return 0;
}