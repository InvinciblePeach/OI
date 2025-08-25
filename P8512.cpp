#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 5e5 + 10;

int n, m, q;
ll ans[MAXN], t[MAXN];

struct Query {
    int l, r, id;

    bool operator<(const Query &o) const { return r < o.r; }
} qry[MAXN];

constexpr int lowbit(const int &x) { return x & -x; }

void add(int x, ll val) {
    for (; x < MAXN; x += lowbit(x))
        t[x] += val;
}

ll query(int x) {
    ll res = 0;
    for (; x; x -= lowbit(x))
        res += t[x];
    return res;
}

struct Opt {
    int l, r, v;
} opt[MAXN];

struct Node {
    int l, r;
    mutable int v, t;

    Node() {}
    Node(const int &L, const int &R, const int &V, const int &T) : l(L), r(R), v(V), t(T) {}

    bool operator<(const Node &o) const { return l < o.l; }
};

set<Node> s;

auto split(int x) {
    auto it = s.lower_bound(Node(x, 0, 0, 0));
    if (it != s.end() && it->l == x) return it;
    --it;
    auto [l, r, v, t] = *it;
    s.erase(it);
    s.emplace(l, x - 1, v, t);
    return s.emplace(x, r, v, t).first;
}

void assign(int l, int r, int v, int t) {
    auto itr = split(r + 1), itl = split(l);
    for (auto it = itl; it != itr; ++it)
        add(it->t, ll(-it->v) * (it->r - it->l + 1));
    s.erase(itl, itr), add(t, ll(v) * (r - l + 1));
    s.emplace(l, r, v, t);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++)
        cin >> opt[i].l >> opt[i].r >> opt[i].v;

    for (int i = 1; i <= q; i++)
        cin >> qry[i].l >> qry[i].r, qry[i].id = i;
    sort(qry + 1, qry + 1 + q);

    s.emplace(1, m, 0, 1);

    for (int i = 1, R = 1; i <= q; i++) {
        for (; R <= qry[i].r; R++)
            assign(opt[R].l, opt[R].r, opt[R].v, R);
        ans[qry[i].id] = query(R) - query(qry[i].l - 1);
    }
    for (int i = 1; i <= q; i++) cout << ans[i] << '\n';

    return 0;
}