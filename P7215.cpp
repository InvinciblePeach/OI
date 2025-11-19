#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 2e5 + 10;
int n, k, rt, S, ans = INT_MAX, a[MAXN], siz[MAXN], mx[MAXN];
bitset<MAXN> vis, use;
vector<int> g[MAXN], pos[MAXN];

void find(int u, int fa) {
    siz[u] = 1, mx[u] = 0;
    for (auto v : g[u]) {
        if (vis[v] || v == fa) continue;
        find(v, u);
        siz[u] += siz[v], mx[u] = max(mx[u], siz[v]);
    }
    mx[u] = max(mx[u], S - siz[u]);
    if (mx[u] < mx[rt]) rt = u;
}

int fa[MAXN];
int st[MAXN], top;
void dfs(int u, int fa) {
    ::fa[u] = fa;
    st[++top] = u, use[u] = 1;
    for (auto v : g[u]) {
        if (vis[v] || v == fa) continue;
        dfs(v, u);
    }
}

void bfs(int s) {
    bitset<MAXN> vis;
    queue<int> q;
    int cnt = 0;
    vis[a[s]] = 1;
    auto push = [&](int k) {
        for (auto u : pos[k]) {
            if (!use[u]) return true;
            q.emplace(u);
        }
        cnt++;
        return false;
    };
    if (push(a[s])) return;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (!vis[a[fa[u]]]) {
            vis[a[fa[u]]] = 1;
            if (push(a[fa[u]])) return;
        }
    }
    ans = min(ans, cnt);
}

void solve(int u) {
    vis[u] = 1;
    dfs(u, u);
    bfs(u);
    while (top) use[st[top]] = 0, top--;
    for (auto v : g[u]) {
        if (vis[v]) continue;
        find(v, u);
        S = siz[v], mx[rt = 0] = INT_MAX;
        find(v, u);
        solve(rt);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> k;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]].emplace_back(i);
    }
    S = n;
    solve(1);
    cout << ans - 1 << '\n';

    return 0;
}