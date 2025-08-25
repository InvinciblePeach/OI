#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 2010;
int n, m, rt, dfn[MAXN], low[MAXN], tot, cnt, d[MAXN];
int st[MAXN], top, f[MAXN], h[MAXN], siz[MAXN];
vector<int> g[MAXN], t[MAXN];

void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++tot;
    st[++top] = u;
    for (auto v : g[u]) {
        if (v == fa) continue;
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                cnt++;
                do {
                    t[cnt].emplace_back(st[top]), t[st[top]].emplace_back(cnt), d[st[top]]++;
                } while (st[top--] ^ v);
                t[cnt].emplace_back(u), t[u].emplace_back(cnt), d[u]++;
            }
        } else low[u] = min(low[u], dfn[v]);
    }
}

void dfs(int u, int fa) {
    h[u] = 1;
    siz[u] = u <= n;
    for (auto v : t[u]) {
        if (v == fa) continue;
        dfs(v, u);
        siz[u] += siz[v];
        if (u <= n) f[u] += max(f[v], 1ll), h[u] *= (f[v] ? h[v] : siz[v]);
        else f[u] += f[v], h[u] *= h[v];
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    for (int T = 1; cin >> m && m; T++) {
        memset(low, 0, sizeof(low));
        memset(dfn, 0, sizeof(dfn));
        memset(siz, 0, sizeof(siz));
        memset(d, 0, sizeof(d));
        memset(f, 0, sizeof(f));
        memset(h, 0, sizeof(h));
        top = n = 0;
        for (int i = 1, u, v; i <= m; i++) {
            cin >> u >> v;
            n = max({n, u, v});
            g[u].emplace_back(v), g[v].emplace_back(u);
        }
        cnt = n;
        tarjan(1, 0);
        for (int i = 1; i <= n; i++)
            if (d[i] >= 2) rt = i;
        dfs(rt, 0);
        if (cnt == n + 1) cout << "Case " << T << ": " << 2 << ' ' << n * (n - 1) / 2 << '\n';
        else cout << "Case " << T << ": " << f[rt] << ' ' << h[rt] << '\n';
        for (int i = 1; i <= cnt; i++) g[i].clear(), t[i].clear();
    }

    return 0;
}