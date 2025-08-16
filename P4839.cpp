#include <bits/stdc++.h>
#define lc(p) p << 1
#define rc(p) p << 1 | 1

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 5e4 + 10;
int n, m;

struct LB {
    int a[32];

    void clear() { memset(a, 0, sizeof(a)); }

    void insert(int x) {
        for (int i = 31; ~i; i--)
            if (x & (1 << i)) {
                if (a[i])
                    x ^= a[i];
                else
                    return a[i] = x, void();
            }
    }

    void merge(const LB &o) {
        for (int i = 31; ~i; i--)
            if (o.a[i]) insert(o.a[i]);
    }
} ans;

struct Node {
    int l, r;
    LB val;
} t[MAXN << 2];

void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(lc(p), l, mid), build(rc(p), mid + 1, r);
}

void modify(int p, int pos, int val) {
    t[p].val.insert(val);
    if (t[p].l == t[p].r) return;
    if (pos <= t[lc(p)].r)
        modify(lc(p), pos, val);
    else
        modify(rc(p), pos, val);
}

void query(int p, int l, int r) {
    if (l <= t[p].l && t[p].r <= r) return ans.merge(t[p].val), void();
    if (l <= t[lc(p)].r) query(lc(p), l, r);
    if (r >= t[rc(p)].l) query(rc(p), l, r);
}

signed main() { 
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> m >> n;
    build(1, 1, n);
    while (m-- > 0) {
        static int op, x, y;
        cin >> op >> x >> y;
        if (op == 1)
            modify(1, x, y);
        else if (op == 2) {
            ans.clear(), query(1, x, y);
            int res = 0;
            for (int i = 31; ~i; i--) res = max(res, res ^ ans.a[i]);
            cout << res << '\n';
        }
    }

    return 0;
}