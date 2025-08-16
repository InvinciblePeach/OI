#include <bits/stdc++.h>
#define lc(p) t[p].lc
#define rc(p) t[p].rc
#define lson lc(p), l, mid
#define rson rc(p), mid + 1, r

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int n = 1e6, MAXN = 1e5 + 10, INF = 0x3f3f3f3f;
int tot, rt[60];

struct Node {
    int lc, rc;
    int mn;
} t[MAXN << 3];

int newnode() {
    ++tot;
    t[tot].lc = t[tot].rc = 0;
    t[tot].mn = INF;
    return tot;
}

void pushup(int p) { t[p].mn = min(t[lc(p)].mn, t[rc(p)].mn); }

void modify(int &p, int l, int r, int pos, int val) {
    if (!p) p = newnode();
    if (l == r) return t[p].mn = min(t[p].mn, val), void();
    int mid = (l + r) >> 1;
    if (pos <= mid) modify(lson, pos, val);
    if (pos > mid) modify(rson, pos, val);
    pushup(p);
}

int query(int p, int l, int r, int L, int R) {
    if (!p) return INF;
    if (L <= l && r <= R) return t[p].mn;
    int mid = (l + r) >> 1;
    int res = INF;
    if (L <= mid) res = min(res, query(lson, L, R));
    if (R > mid) res = min(res, query(rson, L, R));
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int op;
    t[0].mn = INF;
    while (cin >> op) {
        static int x, y, c;
        if (!op) {
            tot = 0;
            memset(rt, 0, sizeof(rt));
        } else if (op == 3)
            break;
        else if (op == 1) {
            cin >> x >> y >> c;
            modify(rt[c], 1, n, y, x);
        } else if (op == 2) {
            cin >> x >> y >> c;
            int cnt = 0;
            for (int i = 50; ~i; i--)
                if (query(rt[i], 1, n, y, c) <= x) cnt++;
            cout << cnt << '\n';
        }
    }

    return 0;
}