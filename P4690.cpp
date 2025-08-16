#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 2e5 + 10, MAXM = 2e6 + 10;
int n, m, a[MAXN], pre[MAXN], pos[MAXN], cnt, num, id;
map<int, int> mp;

struct Node {
    int x, y, t, val, id;
} q[MAXM];

namespace ODT {
    struct Node {
        int l, r;
        mutable int val;

        Node(int L, int R, int V) : l(L), r(R), val(V) {}

        bool operator<(const Node &o) const { return l < o.l; }
    };
    set<Node> t, col[MAXN];

    void del(int l, int r, int val) { col[val].erase({l, r, val}), t.erase({l, r, val}); }

    auto insert(int l, int r, int val) { return col[val].emplace(l, r, val), t.emplace(l, r, val).first; }

    auto split(int p) {
        auto it = t.lower_bound({p, 0, 0});
        if (it->l == p) return it;
        it--;
        auto [l, r, val] = *it;
        del(l, r, val);
        return insert(l, p - 1, val), insert(p, r, val);
    }

    int getpre(int p) {
        auto it = --t.upper_bound({p, 0, 0});
        if (it->l < p) return p - 1;
        it = col[it->val].lower_bound({p, 0, 0});
        if (it != col[it->val].begin()) return (--it)->r;
        return 0;
    }

    void assign(int l, int r, int val, int tim) {
        auto itr = split(r + 1), itl = split(l);
        vector<int> pos;
        for (auto it = itl; it != itr; it++) {
            pos.emplace_back(it->l);
            auto nxt = col[it->val].upper_bound(*it);
            if (nxt != col[it->val].end()) pos.emplace_back(nxt->l);
            col[it->val].erase(*it);
        }
        t.erase(itl, itr);
        insert(l, r, val);
        auto nxt = col[val].upper_bound({l, r, val});
        if (nxt != col[val].end()) pos.emplace_back(nxt->l);
        for (auto p : pos) {
            q[++cnt] = {p, pre[p], tim, -1, 0};
            pre[p] = getpre(p);
            q[++cnt] = {p, pre[p], tim, 1, 0};
        }
    }
}; // namespace ODT

namespace fenwick {
    int t[MAXN];
    constexpr int lowbit(const int &x) { return x & -x; }
    void modify(int x, int val) {
        for (; x < MAXN; x += lowbit(x)) t[x] += val;
    }
    int query(int x) {
        int res = 0;
        for (; x; x -= lowbit(x)) res += t[x];
        return res;
    }
}; // namespace fenwick

int ans[MAXN];

void solve(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    solve(l, mid), solve(mid + 1, r);
    int i = l, j = mid + 1;
    while (j <= r) {
        while (i <= mid && q[i].x <= q[j].x) {
            if (!q[i].id) fenwick::modify(q[i].y + 1, q[i].val);
            i++;
        }
        if (q[j].id) ans[q[j].id] += fenwick::query(q[j].y + 1) * q[j].val;
        j++;
    }
    for (int k = l; k < i; k++)
        if (!q[k].id) fenwick::modify(q[k].y + 1, -q[k].val);
    inplace_merge(q + l, q + 1 + mid, q + r + 1, [](Node a, Node b) { return a.x < b.x; });
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (!mp[a[i]]) mp[a[i]] = ++num;
        a[i] = mp[a[i]];
        pre[i] = pos[a[i]];
        pos[a[i]] = i;
        q[++cnt] = {i, pre[i], 0, 1, 0};
        ODT::insert(i, i, a[i]);
    }
    for (int i = 1; i <= m; i++) {
        static int op, l, r, val;
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> val;
            if (!mp[val]) mp[val] = ++num;
            val = mp[val];
            ODT::assign(l, r, val, i);
        } else {
            cin >> l >> r;
            q[++cnt] = {r, l - 1, i, 1, ++id};
            q[++cnt] = {l - 1, l - 1, i, -1, id};
        }
    }
    sort(q + 1, q + 1 + cnt, [](Node a, Node b) { return a.t < b.t; });
    solve(1, cnt);
    for (int i = 1; i <= id; i++) cout << ans[i] << '\n';

    return 0;
}