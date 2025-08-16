#include <bits/stdc++.h>
#define int long long
#define lc(p) p << 1
#define rc(p) p << 1 | 1

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 2e5 + 10, mod = 1e9 + 7;
int n, q, cnt, tot, w[MAXN], id[MAXN], ed[MAXN], son[MAXN];
vector<pii> qry;
vector<int> g[MAXN];

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}

int inv(int x) { return qpow(x, mod - 2); }

struct Node {
    int l, r;
    int val, mul;
} t[MAXN << 2];

void pushup(int p) { t[p].val = (t[lc(p)].val + t[rc(p)].val) % mod; }

void pushdown(int p) {
    (t[lc(p)].val *= t[p].mul) %= mod;
    (t[rc(p)].val *= t[p].mul) %= mod;
    (t[lc(p)].mul *= t[p].mul) %= mod;
    (t[rc(p)].mul *= t[p].mul) %= mod;
    t[p].mul = 1;
}

void build(int p, int l, int r) {
    t[p] = {l, r, 0, 1};
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(lc(p), l, mid), build(rc(p), mid + 1, r);
    pushup(p);
}

void add(int p, int pos, int val) {
    if (t[p].l == t[p].r) return t[p].val = val, void();

    pushdown(p);
    if (pos <= t[lc(p)].r)
        add(lc(p), pos, val);
    else
        add(rc(p), pos, val);
    pushup(p);
}

void mul(int p, int l, int r, int val) {
    if (l <= t[p].l && t[p].r <= r) {
        (t[p].val *= val) %= mod;
        (t[p].mul *= val) %= mod;
        return;
    }
    pushdown(p);
    if (l <= t[lc(p)].r) mul(lc(p), l, r, val);
    if (r >= t[rc(p)].l) mul(rc(p), l, r, val);
    pushup(p);
}

int query(int p, int l, int r) {
    if (l <= t[p].l && t[p].r <= r) return t[p].val;
    pushdown(p);
    int res = 0;
    if (l <= t[lc(p)].r) (res += query(lc(p), l, r)) %= mod;
    if (r >= t[rc(p)].l) (res += query(rc(p), l, r)) %= mod;
    return res;
}

void dfs(int p) {
    id[p] = ++tot;
    for (auto v : g[p])
        dfs(v);
    ed[p] = tot;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> w[n = 1] >> q;
    for (int i = 1, op, u; i <= q; i++) {
        cin >> op >> u;
        if (op == 1) cin >> w[++n], g[u].emplace_back(n);
        qry.emplace_back(op, u);
    }
    dfs(1);
    build(1, 1, n);
    add(1, 1, w[1]);
    son[1] = 1, n = 1;
    for (auto [op, u] : qry) {
        if (op == 1) {
            ++n;
            add(1, id[n], w[n]);
            mul(1, id[n], id[n], query(1, id[u], id[u]) * inv(w[u]) % mod);
            son[n] = 1, son[u]++;
            mul(1, id[u], ed[u], (son[u]) * inv(son[u] - 1) % mod);
        } else {
            int tmp = w[u] * son[u] % mod * inv(query(1, id[u], id[u])) % mod;
            cout << query(1, id[u], ed[u]) * tmp % mod << '\n';
        }
    }

    return 0;
}