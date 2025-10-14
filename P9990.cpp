#include <bits/stdc++.h>
#define lc(p) p << 1
#define rc(p) p << 1 | 1
#define lson lc(p), l, mid
#define rson rc(p), mid + 1, r

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e6 + 10;
int n, q, a[MAXN], pos[MAXN];
ll ans[MAXN], res;

// #define DEBUG 1 // 调试开关
struct IO {
#define MAXSIZE (1 << 20)
#define isdigit(x) (x >= '0' && x <= '9')
    char buf[MAXSIZE], *p1, *p2;
    char pbuf[MAXSIZE], *pp;
#if DEBUG
#else
    IO() : p1(buf), p2(buf), pp(pbuf) {}

    ~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
#endif
    char gc() {
#if DEBUG // 调试，可显示字符
        return getchar();
#endif
        if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin);
        return p1 == p2 ? ' ' : *p1++;
    }

    bool blank(char ch) { return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t'; }

    template <class T> void read(T &x) {
        double tmp = 1;
        bool sign = 0;
        x = 0;
        char ch = gc();
        for (; !isdigit(ch); ch = gc())
            if (ch == '-') sign = 1;
        for (; isdigit(ch); ch = gc()) x = x * 10 + (ch - '0');
        if (ch == '.')
            for (ch = gc(); isdigit(ch); ch = gc()) tmp /= 10.0, x += tmp * (ch - '0');
        if (sign) x = -x;
    }

    void read(char *s) {
        char ch = gc();
        for (; blank(ch); ch = gc());
        for (; !blank(ch); ch = gc()) *s++ = ch;
        *s = 0;
    }

    void read(char &c) { for (c = gc(); blank(c); c = gc()); }

    void push(const char &c) {
#if DEBUG // 调试，可显示字符
        putchar(c);
#else
        if (pp - pbuf == MAXSIZE) fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
        *pp++ = c;
#endif
    }

    template <class T> void write(T x) {
        if (x < 0) x = -x, push('-'); // 负数输出
        static T sta[35];
        T top = 0;
        do {
            sta[top++] = x % 10, x /= 10;
        } while (x);
        while (top) push(sta[--top] + '0');
    }

    template <class T> void write(T x, char lastChar) { write(x), push(lastChar); }
} io;

struct Matrix {
    int a00, a01, a10, a11;
    ll a02, a12, a22;
    Matrix operator+(const Matrix &y) const {
        Matrix z;
        z.a00 = z.a01 = z.a10 = z.a11 = 0;
        z.a02 = z.a12 = z.a22 = 0;
        z.a00 = (a00 + y.a00);
        z.a01 = (a01 + y.a01);
        z.a02 = (a02 + y.a02);
        return z;
    }
    Matrix operator*(const Matrix &y) const {
        Matrix z;
        z.a22 = a22 * y.a22;
        z.a10 = a10 * y.a00 + a11 * y.a10;
        z.a11 = a10 * y.a01 + a11 * y.a11;
        z.a12 = a10 * y.a02 + a11 * y.a12 + a12 * y.a22;
        z.a00 = a00 * y.a00 + a01 * y.a10;
        z.a01 = a00 * y.a01 + a01 * y.a11;
        z.a02 = a00 * y.a02 + a01 * y.a12 + a02 * y.a22;
        return z;
    }
    bool operator==(const Matrix &y) const {
        return !((a00 ^ y.a00) || (a01 ^ y.a01) || (a02 ^ y.a02) || (a10 ^ y.a10) || (a11 ^ y.a11) || (a12 ^ y.a12) ||
                 (a22 ^ y.a22));
    }
} A, B, C, D, t[MAXN << 2], tag[MAXN << 2];

struct Query {
    int l, r, id;

    bool operator<(const Query &o) const { return r < o.r; }
} qry[MAXN];

void pushdown(int p) {
    if (tag[p] == D) return;
    if (tag[lc(p)] == D)
        tag[lc(p)] = tag[p];
    else
        tag[lc(p)] = tag[lc(p)] * tag[p];
    if (tag[rc(p)] == D)
        tag[rc(p)] = tag[p];
    else
        tag[rc(p)] = tag[rc(p)] * tag[p];
    t[lc(p)] = t[lc(p)] * tag[p];
    t[rc(p)] = t[rc(p)] * tag[p];
    tag[p] = D;
}

void pushup(int p) { t[p] = t[lc(p)] + t[rc(p)]; }

void build(int p, int l, int r) {
    tag[p] = D;
    if (l == r) return t[p] = A, void();
    int mid = (l + r) >> 1;
    build(lson), build(rson);
    pushup(p);
}

void modify(int p, int l, int r, int x, int y, bool op) {
    if (x <= l && r <= y) {
        if (op)
            t[p] = t[p] * B, tag[p] = tag[p] * B;
        else
            t[p] = t[p] * C, tag[p] = tag[p] * C;
        return;
    }
    pushdown(p);
    int mid = (l + r) >> 1;
    if (x <= mid) modify(lson, x, y, op);
    if (y > mid) modify(rson, x, y, op);
    pushup(p);
}

void query(int p, int l, int r, int x, int y) {
    if (x <= l && r <= y) return res += t[p].a02, void();
    pushdown(p);
    int mid = (l + r) >> 1;
    if (x <= mid) query(lson, x, y);
    if (y > mid) query(rson, x, y);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    io.read(n);
    for (int i = 1; i <= n; i++) io.read(a[i]);
    io.read(q);
    for (int i = 1; i <= q; i++) io.read(qry[i].l), io.read(qry[i].r), qry[i].id = i;
    sort(qry + 1, qry + 1 + q);
    A.a00 = 1;
    B.a01 = B.a02 = B.a10 = B.a22 = 1;
    C.a00 = C.a11 = C.a22 = C.a12 = 1;
    D.a00 = D.a11 = D.a22 = 1;
    build(1, 1, n);
    int nw = 1;
    for (int i = 1; i <= q; i++) {
        auto [l, r, id] = qry[i];
        for (; nw <= r; nw++) {
            modify(1, 1, n, pos[a[nw]] + 1, nw, 1);
            if (pos[a[nw]]) modify(1, 1, n, 1, pos[a[nw]], 0);
            pos[a[nw]] = nw;
        }
        res = 0;
        query(1, 1, n, l, r);
        ans[id] = res;
    }
    for (int i = 1; i <= q; i++) io.write(ans[i], '\n');

    return 0;
}