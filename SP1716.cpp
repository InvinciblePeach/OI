#include <bits/stdc++.h>
#define lc(x) x << 1
#define rc(x) x << 1 | 1

using namespace std;
typedef long long ll;

const int MAXN = 5e4 + 10, INF = 0x3f3f3f3f;
int n, m, x[MAXN];

struct Matrix {
    int a[3][3];

    Matrix() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                a[i][j] = -INF;
    }

    void init() {
        for (int i = 0; i < 3; i++) a[i][i] = 0;
    }

    Matrix operator*(const Matrix &o) {
        Matrix res;
        for (int i = 0; i < 3; i++)
            for (int k = 0; k < 3; k++)
                for (int j = 0; j < 3; j++)
                    res.a[i][j] = max(res.a[i][j], a[i][k] + o.a[k][j]);
        return res;
    }
};

struct Node {
    int l, r;
    Matrix tag;
} t[MAXN << 2];

void pushup(int p) { t[p].tag = t[lc(p)].tag * t[rc(p)].tag; }

void build(int p, int l, int r) {
    t[p] = {l, r, Matrix()};
    if (l == r) {
        t[p].tag.a[0][0] = x[l], t[p].tag.a[0][1] = x[l], t[p].tag.a[0][2] = -INF;
        t[p].tag.a[1][0] = -INF, t[p].tag.a[1][1] = 0, t[p].tag.a[1][2] = -INF;
        t[p].tag.a[2][0] = x[l], t[p].tag.a[2][1] = x[l], t[p].tag.a[2][2] = 0;
        return;
    }

    int mid = (l + r) >> 1;
    build(lc(p), l, mid), build(rc(p), mid + 1, r);
    pushup(p);
}

void modify(int p, int pos) {
    if (t[p].l == t[p].r) {
        t[p].tag.a[0][0] = x[pos], t[p].tag.a[0][1] = x[pos], t[p].tag.a[0][2] = -INF;
        t[p].tag.a[1][0] = -INF, t[p].tag.a[1][1] = 0, t[p].tag.a[1][2] = -INF;
        t[p].tag.a[2][0] = x[pos], t[p].tag.a[2][1] = x[pos], t[p].tag.a[2][2] = 0;
        return;
    }

    if (pos <= t[lc(p)].r) modify(lc(p), pos);
    else modify(rc(p), pos);
    pushup(p);
}

Matrix query(int p, int l, int r) {
    if (l <= t[p].l && t[p].r <= r) return t[p].tag;

    Matrix res;
    res.init();
    if (l <= t[lc(p)].r) res = res * query(lc(p), l, r);
    if (r >= t[rc(p)].l) res = res * query(rc(p), l, r);
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> x[i];
    build(1, 1, n);

    cin >> m;
    while (m --> 0) {
        static int opt, x, y;
        cin >> opt >> x >> y;
        if (opt == 0) {
            ::x[x] = y;
            modify(1, x);
        } else if (opt == 1) {
            Matrix res, tmp = query(1, x, y);
            cout << max(tmp.a[0][1], tmp.a[2][1]) << '\n';
        }
    }

    return 0;
}