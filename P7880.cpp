#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e5 + 10, MAXM = 5e5 + 10;
int n, q, ans[MAXN];
map<int, int> pos;
vector<pii> g[MAXN], vec[MAXN];

namespace dsu {
    int son[MAXN], siz[MAXN], dep[MAXN];
    set<int> st;

    void dfs(int u, int fa) {
        siz[u] = 1;
        for (auto [v, w] : g[u]) {
            if (v == fa) continue;
            dep[v] = dep[u] + w;
            dfs(v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
    }

    int pre(int x) {
        auto it = st.lower_bound(x);
        if (it == st.begin()) return 0;
        return *(--it);
    }

    int nxt(int x) {
        auto it = st.upper_bound(x);
        if (it == st.end()) return 0;
        return *it;
    }

    void find(int u, int val) {
        int tmp = pre(u);
        if (tmp) vec[u].emplace_back(tmp, val);
        tmp = nxt(u);
        if (tmp) vec[tmp].emplace_back(u, val);
    }

    void calc(int u, int fa, int val) {
        find(u, val);
        for (auto [v, w] : g[u])
            if (v ^ fa) calc(v, u, val);
    }

    void add(int u, int fa) {
        st.emplace(u);
        for (auto [v, w] : g[u])
            if (v ^ fa) add(v, u);
    }

    void solve(int u, int fa, int op) {
        for (auto [v, w] : g[u])
            if ((v ^ fa) && (v ^ son[u])) solve(v, u, 1);
        if (son[u]) solve(son[u], u, 0);
        find(u, dep[u]);
        st.emplace(u);
        for (auto [v, w] : g[u])
            if ((v ^ fa) && (v ^ son[u])) calc(v, u, dep[u]), add(v, u);
        if (op) st.clear();
    }

    void main() {
        dfs(1, 0);
        solve(1, 0, 0);
        for (int i = 1; i <= n; i++) vec[i].emplace_back(i, dep[i]);
    }
} // namespace dsu

namespace fenwick {
    int t[MAXN];
    constexpr int lowbit(const int &x) { return x & -x; }

    void init() {
        for (int i = 1; i <= n; i++) t[i] = 0;
    }

    void add(int x, int val) {
        if (!x) return;
        for (; x <= n; x += lowbit(x)) t[x] += val;
    }

    int query(int x) {
        int res = 0;
        for (; x; x -= lowbit(x)) res += t[x];
        return res;
    }
} // namespace fenwick

struct Query {
    int l, r, id;

    bool operator<(const Query &o) const { return r < o.r; }
} qry[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> q;
    for (int i = 1, u, v, w; i < n; i++) {
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    dsu::main();
    for (int i = 1; i <= q; i++) cin >> qry[i].l >> qry[i].r, qry[i].id = i;
    sort(qry + 1, qry + 1 + q);
    for (int i = 1, j = 1; i <= n && j <= q; i++) {
        for (auto [l, c] : vec[i])
            if (l > pos[c]) fenwick::add(n - pos[c] + 1, -1), fenwick::add(n - (pos[c] = l) + 1, 1);
        for (; j <= q && qry[j].r <= i; j++) ans[qry[j].id] = fenwick::query(n - qry[j].l + 1);
    }
    for (int i = 1; i <= n; i++) cout << ans[i] << '\n';

    return 0;
}