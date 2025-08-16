#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int c, T, n;
ll sum;

struct Box {
    int a, b, id;
    ll t;

    Box() {}
    Box(const int &A, const int &B, const int &Id, const ll &T)
        : a(A), b(B), id(Id), t(T) {}

    bool operator<(const Box &o) const { return t < o.t; }
} box[MAXN];

struct Node {
    int l, r;
    mutable int w;

    Node() {}
    Node(const int &L, const int &R, const int &W) : l(L), r(R), w(W) {}

    bool operator<(const Node &o) const { return l < o.l; }
};
set<Node> odt;

ll modify(int i) {
    int id = box[i].id;
    auto it = prev(odt.upper_bound({id, 0, 0}));
    auto [L, R, W] = *it;
    if (box[i].a < box[i].b) {
        if (L != id) {
            odt.erase(it);
            odt.emplace(L, id - 1, W);
            it = odt.emplace(id, R, W).first;
        }
        auto itr = it;
        ll res = 0;
        int rpos = id - 1;
        while (itr != odt.end() && itr->w < box[i].b) {
            auto [l, r, w] = *itr++;
            res += ll(r - l + 1) * w, rpos = r;
        }
        odt.erase(it, itr);
        odt.emplace(id, rpos, box[i].b);
        sum += ll(rpos - id + 1) * box[i].b - res;
    } else {
        if (R != id) {
            odt.erase(it);
            odt.emplace(id + 1, R, W);
            it = odt.emplace(L, id, W).first;
        }
        auto itl = it;
        ll res = 0;
        int lpos = id + 1;
        while (itl->w > box[i].b) {
            auto [l, r, w] = *itl;
            res += ll(r - l + 1) * w, lpos = l;
            if (itl == odt.begin()) break;
            itl--;
        }
        odt.erase(prev(odt.upper_bound({lpos, 0, 0})), next(it));
        odt.emplace(lpos, id, box[i].b);
        sum += res - ll(id - lpos + 1) * box[i].b;
    }
    return sum;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> c >> T;
    while (T --> 0) {
        odt.clear(), sum = 0;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> box[i].a >> box[i].b >> box[i].t;
            box[i].a -= i, box[i].b -= i, box[i].id = i;
            odt.emplace(i, i, box[i].a);
        }
        sort(box + 1, box + 1 + n);
        bool flag = true;
        for (int i = 1; i <= n; i++) {
            // cerr << i << ' ' << odt.size() << '\n';
            if (modify(i) > box[i].t) flag = false;
        }
        cout << (flag ? "Yes\n" : "No\n");
    }

    return 0;
}
