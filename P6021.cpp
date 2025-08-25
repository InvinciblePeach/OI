#include <bits/stdc++.h>
#define int long long
#define lc(p) p << 1
#define rc(p) p << 1 | 1

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int n, m, w[MAXN], siz[MAXN], id[MAXN], dfn[MAXN], top[MAXN], ed[MAXN], tot, fa[MAXN], son[MAXN], f[MAXN];
vector<int> g[MAXN];

struct Matrix {
    int a[2][2];

    Matrix() {
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                a[i][j] = INT_MAX;
    }

    void init() { a[0][0] = a[1][1] = 0; }

    constexpr int *operator[](const int &x) { return a[x]; }

    Matrix operator*(const Matrix &o) {
        Matrix res;
        for (int i = 0; i < 2; i++)
            for (int k = 0; k < 2; k++)
                for (int j = 0; j < 2; j++)
                    res[i][j] = min(res[i][j], a[i][k] + o.a[k][j]);
        return res;
    }
} val[MAXN];

void dfs1(int u) {
    siz[u] = 1;
    for (auto v : g[u]) {
        if (v == fa[u]) continue;
        fa[v] = u, dfs1(v);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int top) {
    dfn[id[u] = ++tot] = u;
    ::top[u] = top, ed[top] = max(ed[top], tot);
    val[u][0][0] = 0, val[u][0][1] = w[u], val[u][1][1] = 0;

    if (son[u]) {
        dfs2(son[u], top);
        f[u] += f[son[u]];
    } else return f[u] = val[u][0][0] = w[u], val[u][1][0] = 0, void();
    for (auto v : g[u]) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
        f[u] += f[v], val[u][0][0] += f[v];
    }
    f[u] = min(w[u], f[u]);
}

struct Node {
    int l, r;
    Matrix tag;
} t[MAXN << 2];

void pushup(int p) { t[p].tag = t[lc(p)].tag * t[rc(p)].tag; }

void build(int p, int l, int r) {
    t[p] = {l, r, Matrix()};
    if (l == r) return t[p].tag = val[dfn[l]], void();

    int mid = (l + r) >> 1;
    build(lc(p), l, mid), build(rc(p), mid + 1, r);
    pushup(p);
}

void modify(int p, int x) {
    if (t[p].l == t[p].r) return t[p].tag = val[dfn[x]], void();

    if (x <= t[lc(p)].r) modify(lc(p), x);
    else modify(rc(p), x);
    pushup(p);
}

Matrix query(int p, int l, int r) {
    if (l <= t[p].l && t[p].r <= r) return t[p].tag;

    Matrix res;
    res.init();
    if (l <= t[lc(p)].r) res = res * query(lc(p), l, r);
    if (r >= t[rc(p)].l) res = res * query(rc(p), l, r);
    return res;
}

void update(int u, int w) {
    if (siz[u] == 1) val[u][0][0] += w;
    val[u][0][1] += w;
    ::w[u] += w;

    static Matrix bef, aft;
    while (u) {
        bef = query(1, id[top[u]], ed[top[u]]);
        modify(1, id[u]);
        aft = query(1, id[top[u]], ed[top[u]]);

        u = fa[top[u]];
        val[u][0][0] += aft[0][0] - bef[0][0];
    }
}

int getans(int u) {
    auto ans = query(1, id[u], ed[top[u]]);
    return ans[0][0];
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs1(1), dfs2(1, 1), build(1, 1, n);

    cin >> m;
    while (m --> 0) {
        static char opt;
        static int u, w;
        cin >> opt >> u;
        if (opt == 'Q') cout << getans(u) << '\n';
        else if (opt == 'C') {
            cin >> w;
            update(u, w);
        }
    }

    return 0;
}