#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 2e5 + 10, MAXM = 1e6 + 10;
int n, q, cnt, ans[MAXM];
vector<int> pnt[MAXN];
vector<pii> g[MAXN];

struct Query {
    int l, r, id;
    bool operator<(const Query &o) const { return r == o.r ? id < o.id : r < o.r; }
} qry[MAXM];

namespace dfz {
    int S, rt, siz[MAXN], mx[MAXN], dep[MAXN];
    vector<int> vec;
    bitset<MAXN> vis;

    void find(int u, int fa) {
        siz[u] = 1, mx[u] = 0;
        for (auto [v, w] : g[u]) {
            if (vis[v] || v == fa) continue;
            find(v, u);
            siz[u] += siz[v], mx[u] = max(mx[u], siz[v]);
        }
        mx[u] = max(mx[u], S - siz[u]);
        if (mx[u] < mx[rt]) rt = u;
    }

    void dfs(int u, int fa) {
        vec.emplace_back(u);
        for (auto [v, w] : g[u]) {
            if (vis[v] || v == fa) continue;
            dep[v] = dep[u] + w;
            dfs(v, u);
        }
    }

    int st[MAXN], top;
    void calc(int u) {
        vec.clear();
        dfs(u, 0);
        top = 0;
        sort(vec.begin(), vec.end());
        for (auto p : vec) {
            while (top && dep[p] < dep[st[top]]) pnt[p].emplace_back(st[top--]), cnt++;
            st[++top] = p;
        }
        top = 0;
        reverse(vec.begin(), vec.end());
        for (auto p : vec) {
            while (top && dep[p] < dep[st[top]]) pnt[st[top--]].emplace_back(p), cnt++;
            st[++top] = p;
        }
    }

    void solve(int u) {
        vis[u] = 1;
        calc(u);
        for (auto [v, w] : g[u]) {
            if (vis[v]) continue;
            find(v, u);
            S = siz[v], mx[rt = 0] = INT_MAX;
            find(v, u);
            solve(rt);
        }
    }
} // namespace dfz

namespace chain {
    int fa[MAXN], siz[MAXN], son[MAXN], dep[MAXN], dis[MAXN], top[MAXN];

    void dfs1(int u, int fa) {
        siz[u] = 1, chain::fa[u] = fa;
        for (auto [v, w] : g[u]) {
            if (v == fa) continue;
            dep[v] = dep[u] + 1, dis[v] = dis[u] + w;
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
    }

    void dfs2(int u, int top, int fa) {
        chain::top[u] = top;
        if (son[u]) dfs2(son[u], top, u);
        for (auto [v, w] : g[u]) {
            if (v == fa || v == son[u]) continue;
            dfs2(v, v, u);
        }
    }

    void init() { dfs1(1, 0), dfs2(1, 1, 0); }

    int calc(int u, int v) {
        int res = 0;
        while (top[u] ^ top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            res += dis[u] - dis[fa[top[u]]];
            u = fa[top[u]];
        }
        if (dep[u] < dep[v]) swap(u, v);
        return res + dis[u] - dis[v];
    }
} // namespace chain

namespace fenwick {
    int t[MAXN];
    constexpr int lowbit(const int &x) { return x & -x; }

    void init() { memset(t, 0x3f, sizeof(t)); }

    void add(int x, int val) {
        for (; x < MAXN; x += lowbit(x)) t[x] = min(t[x], val);
    }

    int query(int x) {
        int res = LLONG_MAX;
        for (; x; x -= lowbit(x)) res = min(res, t[x]);
        return res;
    }
} // namespace fenwick

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1, u, v, w; i < n; i++) {
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    cin >> q;
    for (int i = 1; i <= q; i++) cin >> qry[i].l >> qry[i].r, qry[i].id = i;
    dfz::solve(1);
    chain::init();
    fenwick::init();
    sort(qry + 1, qry + 1 + q);
    for (int i = 1, j = 1; j <= q && i <= n; i++) {
        for (auto l : pnt[i]) fenwick::add(n - l + 1, chain::calc(l, i));
        for (; j <= q && qry[j].r <= i; j++) ans[qry[j].id] = fenwick::query(n - qry[j].l + 1);
    }
    for (int i = 1; i <= q; i++) cout << (ans[i] == 0x3f3f3f3f3f3f3f3f ? -1 : ans[i]) << '\n';

    return 0;
}