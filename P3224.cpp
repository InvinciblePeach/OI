#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;
int n, m, q, tot, p[MAXN], id[MAXN], fa[MAXN], rt[MAXN];

struct Node {
    int lc, rc, l, r, sum;
} t[MAXN << 5];

void pushup(int p) { t[p].sum = t[t[p].lc].sum + t[t[p].rc].sum; }

int Modify(int p, const int &l, const int &r, const int &pos, const int &val) {
    if (!p) p = ++tot;
    t[p].l = l, t[p].r = r;
    if (l == r) return t[p].sum += val, p;

    int mid = (l + r) >> 1;
    if (pos <= mid) t[p].lc = Modify(t[p].lc, l, mid, pos, val);
    else t[p].rc = Modify(t[p].rc, mid + 1, r, pos, val);
    return pushup(p), p;
}

int Merge(const int &p, const int &q) {
    if (!p || !q) return p | q;
    if (t[p].l == t[p].r) return t[p].sum += t[q].sum, p;

    t[p].lc = Merge(t[p].lc, t[q].lc), t[p].rc = Merge(t[p].rc, t[q].rc);
    return pushup(p), p;
} 

int query(int p, int k) {
    if (k > t[p].sum) return 0;
    if (t[p].l == t[p].r) return t[p].l;
    
    if (t[p].lc && t[t[p].lc].sum >= k) return query(t[p].lc, k);
    else return query(t[p].rc, k - t[t[p].lc].sum);
}

int get(int p) {
    if (fa[p] == p) return p;
    return fa[p] = get(fa[p]);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    id[0] = -1;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        id[p[i]] = i, fa[i] = i;
        rt[i] = Modify(rt[i], 1, 1e5, p[i], 1);
    }
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        int a = get(u), b = get(v);
        if (a == b) continue;
        rt[a] = Merge(rt[a], rt[b]);
        fa[b] = a;
    }
    cin >> q;
    while (q --> 0) {
        static char op;
        static int x, y, X, Y;
        cin >> op >> x >> y;
        if (op == 'Q') {
            X = get(x);
            cout << id[query(rt[X], y)] << '\n';
        } else {
            X = get(x), Y = get(y);
            rt[X] = Merge(rt[X], rt[Y]);
            fa[Y] = X;
        }
    }

    return 0;
}