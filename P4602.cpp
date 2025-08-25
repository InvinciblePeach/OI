#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;
int n, m, tot, rt[MAXN];

struct Juice {
    int d, l, p;
    bool operator<(const Juice &o) { return d > o.d; }
} num[MAXN];

struct Edge {
    int l, r, lc, rc;
    int sum, val;

    Edge() {}
    Edge(const int &L, const int &R) : l(L), r(R), lc(0), rc(0), sum(0), val(0) {}
} t[MAXN << 5];

int build(int l, int r) {
    int p = ++tot;
    t[p] = {l, r};
    if (l == r) return p;

    int mid = (l + r) >> 1;
    t[p].lc = build(l, mid), t[p].rc = build(mid + 1, r);
    return p;
}

int insert(int pre, int pos) {
    int p = ++tot;
    t[p].l = t[pre].l, t[p].r = t[pre].r;
    t[p].lc = t[pre].lc, t[p].rc = t[pre].rc;
    t[p].sum = t[pre].sum + num[pos].l;
    t[p].val = t[pre].val + num[pos].l * num[pos].p;
    if (t[p].l == t[p].r) return p;

    if (num[pos].p <= t[t[p].lc].r) t[p].lc = insert(t[pre].lc, pos);
    else t[p].rc = insert(t[pre].rc, pos);
    return p;
}

int solve(int p, int val) {
    if (!p) return 0;
    if (t[p].l == t[p].r) return min(t[p].sum, val / t[p].l);
    if (t[t[p].lc].val > val) return solve(t[p].lc, val);
    else return t[t[p].lc].sum + solve(t[p].rc, val - t[t[p].lc].val);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> num[i].d >> num[i].p >> num[i].l;
    sort(num + 1, num + 1 + n);
    rt[0] = build(1, 1e5);
    for (int i = 1; i <= n; i++)
        rt[i] = insert(rt[i - 1], i);

    while (m --> 0) {
        static int g, lim;
        cin >> g >> lim;
        int l = 1, r = n + 1;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (solve(rt[mid], g) < lim) l = mid + 1;
            else r = mid;
        }
        cout << (l != n + 1 ? num[l].d : -1) << '\n';
    }

    return 0;
}