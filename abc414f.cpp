#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5 + 10;
int T, n, k, ans[MAXN], dis[MAXN], vis[MAXN], tim = 1;
vector<int> g[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T-- > 0) {
        int n, k;
        cin >> n >> k;
        for (int i = 1; i <= n; i++)
            g[i].clear(), ans[i] = -1;
        for (int i = 1, u, v; i < n; i++) {
            cin >> u >> v;
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }

        vector<int> cur = {1};
        ans[1] = 0;

        while (!cur.empty()) {
            ++tim;
            queue<int> q;
            for (int u : cur) {
                vis[u] = tim;
                dis[u] = 0;
                q.emplace(u);
            }

            vector<int> nxt;

            while (!q.empty()) {
                int u = q.front(); q.pop();
                if (dis[u] == k) {
                    if (ans[u] == -1 || ans[u] > ans[cur[0]] + 1) {
                        ans[u] = ans[cur[0]] + 1;
                        nxt.emplace_back(u);
                    }
                    continue;
                }
                for (int v : g[u]) {
                    if (vis[v] != tim) {
                        vis[v] = tim;
                        dis[v] = dis[u] + 1;
                        q.emplace(v);
                    }
                }
            }

            cur = nxt;
        }

        for (int k = 2; k <= n; k++)
            cout << ans[k] << " \n"[k == n];
    }
    return 0;
}
