#include <bits/stdc++.h>
#define int long long
#define lc(p) p << 1
#define rc(p) p << 1 | 1

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 1e5 + 10;
int n, m, a[MAXN];

struct Node {
    int l, r;
    int sum[4];
    bool lm[4], rm[4];
} t[MAXN << 2];

void pushup(int p) {
    if (t[lc(p)].rm[0] && t[rc(p)].lm[0]) {
        if (a[t[lc(p)].r] >= a[t[rc(p)].l]) {
            t[p].lm[0] = t[lc(p)].lm[0], t[p].rm[0] = t[rc(p)].rm[1];
            t[p].sum[0] = t[lc(p)].sum[0] + t[rc(p)].sum[1];
        } else {
            t[p].lm[0] = t[lc(p)].lm[2], t[p].rm[0] = t[rc(p)].rm[0];
            t[p].sum[0] = t[lc(p)].sum[2] + t[rc(p)].sum[0];
        }
    } else {
        t[p].lm[0] = t[lc(p)].lm[0], t[p].rm[0] = t[rc(p)].rm[0];
        t[p].sum[0] = t[lc(p)].sum[0] + t[rc(p)].sum[0];
    }

    if (t[lc(p)].rm[1] && t[rc(p)].lm[0]) {
        if (a[t[lc(p)].r] >= a[t[rc(p)].l]) {
            t[p].rm[1] = t[rc(p)].rm[1];
            t[p].sum[1] = t[lc(p)].sum[1] + t[rc(p)].sum[1];
        } else {
            t[p].rm[1] = t[rc(p)].rm[0];
            t[p].sum[1] = t[lc(p)].sum[3] + t[rc(p)].sum[0];
        }
    } else {
        t[p].rm[1] = t[rc(p)].rm[0];
        t[p].sum[1] = t[lc(p)].sum[1] + t[rc(p)].sum[0];
    }

    if (t[lc(p)].rm[0] && t[rc(p)].lm[2]) {
        if (a[t[lc(p)].r] >= a[t[rc(p)].l]) {
            t[p].lm[2] = t[lc(p)].lm[0];
            t[p].sum[2] = t[lc(p)].sum[0] + t[rc(p)].sum[3];
        } else {
            t[p].lm[2] = t[lc(p)].lm[2];
            t[p].sum[2] = t[lc(p)].sum[2] + t[rc(p)].sum[2];
        }
    } else {
        t[p].lm[2] = t[lc(p)].lm[0];
        t[p].sum[2] = t[lc(p)].sum[0] + t[rc(p)].sum[2];
    }

    if (t[lc(p)].rm[1] && t[rc(p)].lm[2]) {
        if (a[t[lc(p)].r] >= a[t[rc(p)].l]) {
            t[p].sum[3] = t[lc(p)].sum[1] + t[rc(p)].sum[3];
        } else {
            t[p].sum[3] = t[lc(p)].sum[3] + t[rc(p)].sum[2];
        }
    } else {
        t[p].sum[3] = t[lc(p)].sum[1] + t[rc(p)].sum[2];
    }
}

void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    if (l == r) {
        t[p].sum[0] = a[l];
        t[p].lm[0] = t[p].rm[0] = true;
        return;
    }
    int mid = (l + r) >> 1;
    build(lc(p), l, mid), build(rc(p), mid + 1, r);
    pushup(p);
}

void modify(int p, int pos, int val) {
    if (t[p].l == t[p].r) return t[p].sum[0] = val, void();
    if (pos <= t[lc(p)].r)
        modify(lc(p), pos, val);
    else
        modify(rc(p), pos, val);
    pushup(p);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> m;
    build(1, 1, n);
    while (m-- > 0) {
        static int x, y;
        cin >> x >> y;
        modify(1, x, a[x] = y);
        cout << t[1].sum[0] << '\n';
    }

    return 0;
}