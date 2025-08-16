#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;
int n, son[MAXN], siz[MAXN], fa[MAXN], col[MAXN];
int Ans[MAXN], q[MAXN], top, cnt[MAXN], ans, tmp;
vector<int> g[MAXN];

void dfs(int u) {
    siz[u] = 1;
    for (auto v : g[u]) {
        if (v == fa[u]) continue;
        fa[v] = u, dfs(v);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}

void insert(int x) {
    cnt[q[++top] = x]++;
    if (cnt[x] > tmp) tmp = cnt[ans = x];
    else if (cnt[x] == tmp) ans += x;
}

void clean() {
    ans = tmp = 0;
    while (top) cnt[q[top--]]--;
}

void add(int u) {
    insert(col[u]);
    for (auto v : g[u]) {
        if (v == fa[u]) continue;
        add(v);
    }
}

void solve(int u) {
    for (auto v : g[u]) {
        if (v == fa[u] || v == son[u]) continue;
        solve(v), clean();
    }
    if (son[u]) solve(son[u]);
    for (auto v : g[u]) {
        if (v == fa[u] || v == son[u]) continue;
        add(v);
    }
    insert(col[u]), Ans[u] = ans;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> col[i];
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs(1), solve(1);
    for (int i = 1; i <= n; i++)
        cout << Ans[i] << " \n"[i == n];

    return 0;
}