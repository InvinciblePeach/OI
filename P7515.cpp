#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 610;
int T, n, m, b[MAXN][MAXN], a[MAXN][MAXN], tim[MAXN], dis[MAXN];
bitset<MAXN> vis;
struct Edge {
    int v, w;

    Edge(int V, int W) : v(V), w(W) {}
};
vector<Edge> g[MAXN];
queue<int> q;

void solve() {
    cin >> n >> m;
    int k = n + 1 + m;
    for (int i = 1; i <= n - 1; i++)
        for (int j = 1; j <= m - 1; j++)
            cin >> b[i][j];
    memset(a, 0, sizeof(a));
    for (int i = n - 1; i; i--)
        for (int j = m - 1; j; j--)
            a[i][j] = b[i][j] - a[i + 1][j] - a[i][j + 1] - a[i + 1][j + 1];
    for (int i = 1; i <= n + m; i++)
        g[i].clear();

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int mx = 1e6 - a[i][j], mn = a[i][j];
            if ((i + j) & 1)
                g[j + n].emplace_back(i, mx), g[i].emplace_back(j + n, mn);
            else
                g[j + n].emplace_back(i, mn), g[i].emplace_back(j + n, mx);
        }
    }
    queue<int>().swap(q);
    for (int i = 1; i <= n + m; i++)
        dis[i] = tim[i] = 0, vis[i] = 1, q.emplace(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (auto [v, w] : g[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (!vis[v]) {
                    if (++tim[v] > k) return cout << "NO\n", void();
                    vis[v] = 1;
                    q.emplace(v);
                }
            }
        }
    }
    cout << "YES\n";
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cout << a[i][j] + (((i + j) & 1) ? dis[i] - dis[j + n] : dis[j + n] - dis[i]) << " \n"[j == m];
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T-- > 0)
        solve();

    return 0;
}