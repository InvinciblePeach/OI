#include <bits/stdc++.h>
#define int long long
#define lc(p) (p) << 1
#define rc(p) (p) << 1 | 1

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e5 + 10;
int n, m, a[MAXN];
struct Node {
    int l, r;
    int mx, sum;
} t[MAXN << 2];

void pushup(int p) { t[p].sum = t[lc(p)].sum + t[rc(p)].sum, t[p].mx = max(t[lc(p)].mx, t[rc(p)].mx); }

void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    if (l == r) return t[p].sum = t[p].mx = a[l], void();
    int mid = (l + r) >> 1;
    build(lc(p), l, mid), build(rc(p), mid + 1, r);
    pushup(p);
}

void modify(int p, int l, int r) {
    if (t[p].mx == 1) return;
    if (t[p].l == t[p].r) return t[p].mx = t[p].sum = sqrt(t[p].sum), void();
    if (l <= t[lc(p)].r) modify(lc(p), l, r);
    if (r >= t[rc(p)].l) modify(rc(p), l, r);
    pushup(p);
}

int query(int p, int l, int r) {
    if (l <= t[p].l && t[p].r <= r) return t[p].sum;
    int res = 0;
    if (l <= t[lc(p)].r) res += query(lc(p), l, r);
    if (r >= t[rc(p)].l) res += query(rc(p), l, r);
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
    cin >> m;
    while (m-- > 0) {
        static int op, l, r;
        cin >> op >> l >> r;
        if (l > r) swap(l, r);
        if (op)
            cout << query(1, l, r) << '\n';
        else
            modify(1, l, r);
    }
    return 0;
}