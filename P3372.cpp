#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 100010;
struct Node {
    int l, r;
    int sum, tag;
} t[MAXN << 2];
int v[MAXN], n, m;

void pushup(int p) { t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum; }

void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    if (l == r) {
        t[p].sum = v[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

void modify(int p, int val, int l, int r) {
    if (l == t[p].l && t[p].r == r) {
        t[p].sum += val * (t[p].r - t[p].l + 1);
        t[p].tag += val;
        return;
    }
    if (r <= t[p << 1].r) return modify(p << 1, val, l, r);
    if (l >= t[p << 1 | 1].l) return modify(p << 1 | 1, val, l, r);
    return modify(p << 1, val, l, t[p << 1].r), modify(p << 1 | 1, val, t[p << 1 | 1].l, r);
}

int query(int p, int l, int r, int k) {
    if (l == t[p].l && r == t[p].r) return t[p].sum + k * (t[p].r - t[p].l + 1);
    if (r <= t[p << 1].r) return query(p << 1, l, r, k + t[p].tag);
    if (l >= t[p << 1 | 1].l) return query(p << 1 | 1, l, r, k + t[p].tag);
    return query(p << 1, l, t[p << 1].r, k + t[p].tag) +
           query(p << 1 | 1, t[p << 1 | 1].l, r, k + t[p].tag);
}

signed main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> v[i];
    build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int x, y, k;
            cin >> x >> y >> k;
            modify(1, k, x, y);
        } else {
            int x, y;
            cin >> x >> y;
            cout << query(1, x, y, 0) << endl;
        }
    }
    return 0;
}