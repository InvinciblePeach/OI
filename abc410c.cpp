#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 10;
int n, m, tot, rt, a[MAXN];

struct node {
    int l, r;
    int val, dat;
    int siz, tag;
} t[MAXN];

int New(int val) {
    t[++tot].val = val;
    t[tot].dat = rand();
    t[tot].siz = 1;
    return tot;
}

void pushup(int p) { t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1; }

void Split(int p, int rk, int &x, int &y) {
    if (!p) return x = y = 0, void();

    if (t[t[p].l].siz < rk) {
        x = p;
        Split(t[p].r, rk - t[t[p].l].siz - 1, t[p].r, y);
    } else {
        y = p;
        Split(t[p].l, rk, x, t[p].l);
    }
    pushup(p);
}

int Merge(int x, int y) {
    if (!x || !y) return x | y;

    if (t[x].dat > t[y].dat) {
        t[x].r = Merge(t[x].r, y);
        pushup(x);
        return x;
    } else {
        t[y].l = Merge(x, t[y].l);
        pushup(y);
        return y;
    }
}

void walk(int p) {
    if (!p) return;
    walk(t[p].l);
    cout << t[p].val << ' ';
    walk(t[p].r);
}

void modify(int p, int k, int val) {
    if (!k) return t[p].val = val, void();
    if (t[t[p].l].siz < k) modify(t[p].r, k - t[t[p].l].siz - 1, val);
    else modify(t[p].l, k, val);
}

int query(int p, int k) {
    if (!k) return t[p].val;
    if (t[t[p].l].siz < k) return query(t[p].r, k - t[t[p].l].siz - 1);
    else return query(t[p].l, k);
}

signed main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) rt = Merge(rt, New(i));

    while (m --> 0) {
        static int op, p, k;
        static int x, y, z;
        cin >> op >> p;
        if (op == 1) {
            cin >> k;
            Split(rt, p - 1, x, y);
            Split(y, 1, y, z);
            t[y].val = k;
            rt = Merge(x, Merge(y, z));
        } else if (op == 2) {
            Split(rt, p - 1, x, y);
            Split(y, 1, y, z);
            cout << t[y].val << '\n';
            rt = Merge(x, Merge(y, z));
        } else {
            p %= n;
            Split(rt, p, y, z);
            rt = Merge(z, y);
        }
    }
    return 0;
}