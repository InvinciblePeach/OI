#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int n, r, c, tot, cnt, scc[MAXN], siz[MAXN], id[MAXN], low[MAXN];
int top, ans, st[MAXN], in[MAXN], f[MAXN];
int dx[]{0, 0, 1, -1, 1, -1, 1, -1};
int dy[]{1, -1, 0, 0, 1, -1, -1, 1};
bitset<MAXN> vis;
vector<int> g[MAXN], t[MAXN];

struct Point {
    int x, y, t;
    Point() {}
    Point(const int &X, const int &Y) : x(X), y(Y) {}
    bool operator<(const Point &o) { return x == o.x ? y < o.y : x < o.x; }
} p[MAXN];

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
        vis[u] = 0, siz[scc[u] = ++cnt] += (u > r + c);
        while (st[top] != u)
            vis[st[top]] = 0, siz[scc[st[top]] = cnt] += (st[top] > r + c), top--;
        top--;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> r >> c;
    for (int i = 1; i <= n; i++)
        cin >> p[i].x >> p[i].y >> p[i].t;
    sort(p + 1, p + 1 + n);
    for (int i = 1; i <= n; i++) {
        g[p[i].x].emplace_back(r + c + i);
        g[r + p[i].y].emplace_back(r + c + i);
        if (p[i].t == 1) g[r + c + i].emplace_back(p[i].x);
        else if (p[i].t == 2) g[r + c + i].emplace_back(r + p[i].y);
        else if (p[i].t == 3) {
            for (int k = 0; k < 8; k++) {
                int xx = p[i].x + dx[k], yy = p[i].y + dy[k];
                if (xx >= 1 && xx <= r && yy >= 1 && yy <= c) {
                    int id = lower_bound(p + 1, p + 1 + n, Point(xx, yy)) - p;
                    if (id != n + 1 && p[id].x == xx && p[id].y == yy) g[r + c + i].emplace_back(r + c + id);
                }
            }
        }
    }

    for (int i = 1; i <= r + c + n; i++)
        if (!id[i]) tarjan(i);

    for (int u = 1; u <= r + c + n; u++)
        for (auto v : g[u])
            if (scc[u] != scc[v]) t[scc[u]].emplace_back(scc[v]), in[scc[v]]++;

    queue<int> q;
    for (int i = 1; i <= cnt; i++) if (!in[i]) q.emplace(i), f[i] = siz[i];
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : t[u]) {
            f[v] = max(f[v], f[u] + siz[v]);
            if (!--in[v]) q.emplace(v);
        }
    }

    for (int i = 1; i <= cnt; i++)
        ans = max(ans, f[i]);
    cout << ans << '\n';

    return 0;
}