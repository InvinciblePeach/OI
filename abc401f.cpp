#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 2e5 + 10;
int n, m, ans, d1, d2, dis1[MAXN], dis2[MAXN];
vector<int> g[MAXN], t[MAXN];

void dfs(int u, int fa, int &rt, int *dis, vector<int> *G) {
    for (auto v : G[u]) {
        if (v == fa) continue;
        if (dis[rt] < (dis[v] = max(dis[v], dis[u] + 1))) rt = v;
        dfs(v, u, rt, dis, G);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    cin >> m;
    for (int i = 1, u, v; i < m; i++) {
        cin >> u >> v;
        t[u].emplace_back(v);
        t[v].emplace_back(u);
    }

    {
        static int u = 0, v = 0;
        static int dis1[MAXN], dis2[MAXN];
        dfs(1, 0, u, dis1, g);
        dfs(u, 0, v, dis2, g);
        memset(dis1, 0, sizeof(dis1));
        dfs(v, 0, u, dis1, g);
        d1 = dis1[u];
        for (int i = 1; i <= n; i++)
            ::dis1[i] = max(dis1[i], dis2[i]);
    }
    {
        static int u = 0, v = 0;
        static int dis1[MAXN], dis2[MAXN];
        dfs(1, 0, u, dis1, t);
        dfs(u, 0, v, dis2, t);
        memset(dis1, 0, sizeof(dis1));
        dfs(v, 0, u, dis1, t);
        d2 = dis1[u];
        for (int i = 1; i <= m; i++)
            ::dis2[i] = max(dis1[i], dis2[i]);
    }
    cerr << d1 << ' ' << d2 << '\n';

    sort(dis1 + 1, dis1 + n + 1);
    sort(dis2 + 1, dis2 + m + 1);

    int sum = 0;
    for (int i = 1, j = m; i <= n; i++) {
        while (j && dis1[i] + dis2[j] + 1 >= max(d1, d2)) sum += dis2[j--] + 1;
        cerr << dis1[i] << ' ' << dis2[j] << ' ' << sum << '\n';
        ans += sum + dis1[i] * (m - j) + j * max(d1, d2);
    }
    cout << ans << '\n';

    return 0;
}