#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 1e5 + 10;
int n, m, q, a[MAXN];

struct Node {
    int l, r;
    mutable int val;

    Node(int L, int R, int V) : l(L), r(R), val(V) {}

    bool operator<(const Node &o) const { return l < o.l; }
};
set<Node> odt;

struct Query {
    int l, r, op;
} qry[MAXN];

auto split(int pos) {
    auto it = odt.lower_bound({pos, 0, 0});
    if (it != odt.end() && it->l == pos) return it;
    it--;
    int val = it->val, l = it->l, r = it->r;
    odt.erase(it);
    return odt.emplace(l, pos - 1, val), odt.emplace(pos, r, val).first;
}

void modify(int l, int r, int op) {
    auto itr = split(r + 1), itl = split(l);
    int cnt[2] = {0, 0};
    for (auto it = itl; it != itr; it++) cnt[it->val] += it->r - it->l + 1;
    odt.erase(itl, itr);
    if (op == 0) {
        if (l <= l + cnt[0] - 1) odt.emplace(l, l + cnt[0] - 1, 0);
        if (l + cnt[0] <= r) odt.emplace(l + cnt[0], r, 1);
    } else {
        if (l <= l + cnt[1] - 1) odt.emplace(l, l + cnt[1] - 1, 1);
        if (l + cnt[1] <= r) odt.emplace(l + cnt[1], r, 0);
    }
}

bool check(int x) {
    odt.clear();
    for (int i = 1; i <= n; i++) odt.emplace(i, i, a[i] >= x);
    for (int i = 1; i <= m; i++) {
        int l = qry[i].l, r = qry[i].r, op = qry[i].op;
        modify(l, r, op);
    }
    return split(q)->val;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> qry[i].op >> qry[i].l >> qry[i].r;
    cin >> q;
    int l = 1, r = n, res;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid))
            res = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    cout << res << '\n';

    return 0;
}