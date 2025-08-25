#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;
int n, m, X, Y;

struct Ans {
    int dis, id;

    bool operator<(const Ans &o) { return dis == o.dis ? id < o.id : dis < o.dis; }
};

struct Point {
    int x[2], id;

    bool operator<(const Point &o) { return x[id] < o.x[id]; }
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
    int l = t[p].lc, r = t[p].rc;
    if (l)
        t[p].mn[0] = min(t[p].mn[0], t[l].mn[0]), t[p].mn[1] = min(t[p].mn[1], t[l].mn[1]),
        t[p].mx[0] = max(t[p].mx[0], t[l].mx[0]), t[p].mx[1] = max(t[p].mx[1], t[l].mx[1]);
    if (r)
        t[p].mn[0] = min(t[p].mn[0], t[r].mn[0]), t[p].mn[1] = min(t[p].mn[1], t[r].mn[1]),
        t[p].mx[0] = max(t[p].mx[0], t[r].mx[0]), t[p].mx[1] = max(t[p].mx[1], t[r].mx[1]);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    /*code*/

    return 0;
}