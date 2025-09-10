#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;
int n, m, X, Y;

struct Ans {
    int dis, id;
    Ans(int D, int I) : dis(D), id(I) {}
    bool operator<(const Ans &o) const { return dis == o.dis ? id < o.id : dis > o.dis; }
};
priority_queue<Ans> q;

struct Point {
    int x[2], id;
} p[MAXN];

struct Node {
    Point p;
    int lc, rc, id;
    int mn[2], mx[2];
} t[MAXN];

int dis(const Node &x) { return (x.p.x[0] - X) * (x.p.x[0] - X) + (x.p.x[1] - Y) * (x.p.x[1] - Y); }

int mxdis(const Node &x) {
    int P = (x.mn[0] - X) * (x.mn[0] - X);
    int M = (x.mx[0] - X) * (x.mx[0] - X);
    int Q = (x.mn[1] - Y) * (x.mn[1] - Y);
    int N = (x.mx[1] - Y) * (x.mx[1] - Y);
    return max(P, M) + max(Q, N);
}

void pushup(int p) {
    if (!p) return;
    int lc = t[p].lc, rc = t[p].rc;
    if (lc)
        t[p].mn[0] = min(t[p].mn[0], t[lc].mn[0]), t[p].mn[1] = min(t[p].mn[1], t[lc].mn[1]),
        t[p].mx[0] = max(t[p].mx[0], t[lc].mx[0]), t[p].mx[1] = max(t[p].mx[1], t[lc].mx[1]);
    if (rc)
        t[p].mn[0] = min(t[p].mn[0], t[rc].mn[0]), t[p].mn[1] = min(t[p].mn[1], t[rc].mn[1]),
        t[p].mx[0] = max(t[p].mx[0], t[rc].mx[0]), t[p].mx[1] = max(t[p].mx[1], t[rc].mx[1]);
}

void query(int p) {
    if (!p) return;
    int res = dis(t[p]);
    if (res > q.top().dis || (res == q.top().dis && t[p].id < q.top().id)) q.pop(), q.emplace(res, t[p].id);
    int lc = t[p].lc, rc = t[p].rc, ld = 0, rd = 0;
    if (lc) ld = mxdis(t[lc]);
    if (rc) rd = mxdis(t[rc]);
    if (ld > rd) {
        if (ld >= q.top().dis) query(lc);
        if (rd >= q.top().dis) query(rc);
    } else {
        if (rd >= q.top().dis) query(rc);
        if (ld >= q.top().dis) query(lc);
    }
}

int tot;
int build(int l, int r, int w) {
    if (l > r) return 0;
    int mid = (l + r) >> 1, nw = ++tot;
    nth_element(p + l, p + mid, p + r + 1, [w](Point a, Point b) { return a.x[w] < b.x[w]; });
    t[nw].p = p[mid], t[nw].id = p[mid].id;
    t[nw].mn[0] = t[nw].mx[0] = p[mid].x[0];
    t[nw].mn[1] = t[nw].mx[1] = p[mid].x[1];
    t[nw].lc = build(l, mid - 1, w ^ 1), t[nw].rc = build(mid + 1, r, w ^ 1);
    return pushup(nw), nw;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i].x[0] >> p[i].x[1], p[i].id = i;
    int rt = build(1, n, 0);
    cin >> m;
    while (m-- > 0) {
        static int k;
        cin >> X >> Y >> k;
        priority_queue<Ans>().swap(q);
        for (int i = 1; i <= k; i++) q.emplace(-1, 0);
        query(rt);
        cout << q.top().id << '\n';
    }

    return 0;
}