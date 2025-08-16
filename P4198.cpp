#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
const int MAXN = 1e5 + 10;
int n, m;
ld a[MAXN];

struct Node {
    int l, r, len;
    ld mx;
} t[MAXN << 2];

int pushup(const int &p, const ld &mx) {
    if (a[t[p].l] > mx) return t[p].len;
    if (t[p].mx <= mx) return 0;
    if (t[p].l == t[p].r) return t[p].mx > mx;
    if (t[p << 1].mx <= mx) return pushup(p << 1 | 1, mx);
    else return pushup(p << 1, mx) + t[p].len - t[p << 1].len;
}

constexpr void build(const int &p, const int &l, const int &r) {
    t[p].l = l, t[p].r = r;
    if (l == r) return;
    int mid = l + r >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
}

void modify(const int &p, const int &pos, const int &val) {
    if (t[p].l == t[p].r) {
        t[p].mx = ld(val) / pos;
        t[p].len = 1;
        return;
    }
    int mid = t[p].l + t[p].r >> 1;
    if (pos <= mid) modify(p << 1, pos, val);
    else modify(p << 1 | 1, pos, val);
    t[p].mx = max(t[p << 1].mx, t[p << 1 | 1].mx);
    t[p].len = t[p << 1].len + pushup(p << 1 | 1, t[p << 1].mx);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    build(1, 1, n);
    while (m --> 0) {
        int x, y;
        cin >> x >> y;
        a[x] = ld(y) / x;
        modify(1, x, y);
        cout << t[1].len << '\n';
    }

    return 0;
}