#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 4e5 + 10;
int n, m, fa[MAXN], siz[MAXN];
double sum[MAXN];

struct Node {
    int val;
    mutable int cnt;

    Node(int V, int C) : val(V), cnt(C) {}

    bool operator<(const Node &o) const { return val < o.val; }
};
set<Node> odt[MAXN];

void insert(int p, int val, int cnt) {
    auto it = odt[p].lower_bound({val, 0});
    if (it->val == val)
        it->cnt += cnt;
    else
        odt[p].emplace(val, cnt);
    sum[p] += cnt * log(val);
}

int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }

void merge(int x, int y) {
    int fax = get(x), fay = get(y);
    if (odt[fax].size() < odt[fay].size()) swap(odt[fax], odt[fay]);
    for (auto p : odt[fay]) insert(fax, p.val, p.cnt);
    fa[fay] = fax;
    siz[fax] += siz[fay];
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> m;
    while (m-- > 0) {
        static int op, x, y;
        cin >> op;
        if (op == 1) {
            cin >> x;
            odt[++n].emplace(x, 1);
            sum[n] = log(x);
            fa[n] = n, siz[n] = 1;
        } else if (op == 2) {
            cin >> x >> y;
            merge(x, y);
        } else if (op == 3) {
            // for (auto p : odt[get(5)]) cerr << p.val << ':' << p.cnt << '\n';
            cin >> x >> y;
            int fax = get(x);
            int sum = 0;
            auto it = odt[fax].begin();
            for (; it != odt[fax].end() && it->val <= y; it++) sum += it->cnt;
            odt[fax].erase(odt[fax].begin(), it);
            insert(fax, y, sum);
        } else if (op == 4) {
            cin >> x >> y;
            int fax = get(x);
            int sum = 0;
            auto it = odt[fax].end();
            it--;
            for (; it != odt[fax].begin() && it->val >= y; it--) sum += it->cnt;
            odt[fax].erase(it, odt[fax].end());
            insert(fax, y, sum);
        } else if (op == 5) {
            cin >> x >> y;
            int fax = get(x);
            int sum = 0;
            auto it = odt[fax].begin();
            for (; it != odt[fax].end() && sum < y; it++) sum += it->cnt;
            cout << it->val << '\n';
        } else if (op == 6) {
            cin >> x >> y;
            int fax = get(x), fay = get(y);
            cout << (sum[fax] > sum[fay]) << '\n';
        } else if (op == 7) {
            cin >> x;
            cout << siz[get(x)] << '\n';
        }
    }

    return 0;
}