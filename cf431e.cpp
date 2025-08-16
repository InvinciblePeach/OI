#include <bits/stdc++.h>
#define int long long
#define lc(p) t[p].lc
#define rc(p) t[p].rc
#define lson lc(p), l, mid
#define rson rc(p), mid + 1, r

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 1e5 + 10, M = 1e9;
int n, q, tot, rt, h[MAXN];

struct Node {
    int lc, rc;
    int sum, siz;
} t[MAXN << 5];

void pushup(int p) { t[p].sum = t[lc(p)].sum + t[rc(p)].sum, t[p].siz = t[lc(p)].siz + t[rc(p)].siz; }

void modify(int &p, int l, int r, int pos, int val) {
    if (!p) p = ++tot;
    if (l == r) return t[p].sum += val * l, t[p].siz += val, void();
    int mid = (l + r) >> 1;
    if (pos <= mid) modify(lson, pos, val);
    if (pos > mid) modify(rson, pos, val);
    pushup(p);
}

int cnt, all;

int query(int p, int l, int r, int lim) {
    if (!p) return l;
    if (l == r) return cnt += t[p].siz, all += t[p].sum, l;
    int mid = (l + r) >> 1, res = (t[lc(p)].siz + cnt) * (mid + 1) - t[lc(p)].sum - all;
    if (res >= lim)
        return query(lson, lim);
    else
        return cnt += t[lc(p)].siz, all += t[lc(p)].sum, query(rson, lim);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> h[i], modify(rt, 0, M, h[i], 1);
    while (q-- > 0) {
        static int op, x, y;
        cin >> op >> x;
        if (op == 1) {
            cin >> y;
            modify(rt, 0, M, h[x], -1);
            modify(rt, 0, M, h[x] = y, 1);
        } else {
            cnt = all = 0;
            int val = query(rt, 0, M, x);
            double tmp = 1.0 * (x - val * cnt + all) / cnt;
            printf("%.5lf\n", val + tmp);
        }
    }

    return 0;
}