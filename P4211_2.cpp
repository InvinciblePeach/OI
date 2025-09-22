#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 5e4 + 10, mod = 201314;
int n, m, son[MAXN], siz[MAXN], ans[MAXN];
int st[MAXN], sum[MAXN], top;
vector<int> g[MAXN];

void dfs1(int u, int fa) {
    siz[u] = 1;
    for (auto v : g[u]) {
        if (v == fa) continue;
        dfs1(v, u);
        if (siz[v] > siz[son[u]]) son[u] = v;
        siz[u] += siz[v];
    }
}

struct Node {
    int lc, rc, siz, sum, fa, tag;
} t[MAXN];

#define lc(p) t[p].lc
#define rc(p) t[p].rc

int build(int l, int r) {
    if (l > r) return 0;
    int mid = lower_bound(sum + l, sum + 1 + r, (sum[r] + sum[l]) >> 1) - sum, p = st[mid];
    t[p].siz = r - l + 1;
    lc(p) = build(l, mid - 1);
    rc(p) = build(mid + 1, r);
    if (lc(p)) t[lc(p)].fa = p;
    if (rc(p)) t[rc(p)].fa = p;
    return p;
}

int dfs2(int u, int fa) {
    int rt = 0;
    st[++top] = u;
    sum[top] = sum[top - 1] + siz[u] - siz[son[u]];
    if (son[u])
        rt = dfs2(son[u], u);
    else {
        int p = build(1, top);
        top = 0;
        return p;
    }
    for (auto v : g[u]) {
        if (v == fa || v == son[u]) continue;
        t[dfs2(v, u)].fa = u;
    }
    return rt;
}

void add(int u) {
    bool flag = true;
    int val = 0;
    while (u) {
        t[u].sum += val;
        if (flag) {
            t[u].tag++;
            if (rc(u)) t[rc(u)].tag--;
            val += 1 + t[lc(u)].siz;
            t[u].sum -= t[rc(u)].siz;
        }
        flag = (u != lc(t[u].fa));
        if (flag && u != rc(t[u].fa)) val = 0;
        u = t[u].fa;
    }
}

int query(int u) {
    bool flag = true;
    int res = 0, val = 0;
    while (u) {
        if (flag) {
            res += t[u].sum - t[rc(u)].sum;
            res -= t[rc(u)].siz * t[rc(u)].tag;
            val += 1 + t[lc(u)].siz;
        }
        res += val * t[u].tag;
        flag = (u != lc(t[u].fa));
        if (flag && u != rc(t[u].fa)) val = 0;
        u = t[u].fa;
    }
    return res;
}

struct Query {
    int p, z, id, val;

    Query() {}
    Query(int P, int Z, int Id, int Val) : p(P), z(Z), id(Id), val(Val) {}

    constexpr bool operator<(const Query &o) { return p < o.p; }
} q[MAXN << 1];
int cnt = 0;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 2, p; i <= n; i++) {
        cin >> p;
        g[++p].emplace_back(i);
    }
    for (int i = 1, l, r, z; i <= m; i++) {
        cin >> l >> r >> z;
        r++, z++;
        q[++cnt] = {l, z, i, -1};
        q[++cnt] = {r, z, i, 1};
    }
    dfs1(1, 1), dfs2(1, 1);
    for (int i = 1; i <= n; i++) cerr << t[i].fa << " \n"[i == n];
    sort(q + 1, q + 1 + cnt);
    int nw = 0;
    for (int i = 1; i <= cnt; i++) {
        while (nw < q[i].p) add(++nw);
        (ans[q[i].id] += query(q[i].z) * q[i].val) %= mod;
    }
    for (int i = 1; i <= m; i++) cout << (ans[i] + mod) % mod << '\n';

    return 0;
}