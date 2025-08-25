#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 5e5 + 10;
int n, m, rt, dfn[MAXN], low[MAXN], tot, cnt, d[MAXN];
int st[MAXN], top;
vector<int> g[MAXN], ans[MAXN];

void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++tot;
    st[++top] = u;
    int son = 0;
    for (auto v : g[u]) {
        if (v == fa) continue;
        if (!dfn[v]) {
            son++;
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                cnt++;
                do {
                    ans[cnt].emplace_back(st[top]);
                } while (st[top--] ^ v);
                ans[cnt].emplace_back(u);
            }
        } else low[u] = min(low[u], dfn[v]);
    }
    if (!fa && !son) ans[++cnt].push_back(u);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        g[u].emplace_back(v), g[v].emplace_back(u);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) top = 0, tarjan(i, 0);
    cout << cnt << '\n';

	for(int i = 1; i <= cnt; i++) {
		cout << ans[i].size() << ' ';
		for(int j : ans[i]) cout << j << ' ';
        cout << '\n';
	}

    return 0;
}