#include <bits/stdc++.h>
#define DEBUG 1 // 调试开关

using namespace std;

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

    bool blank(char ch) {
        return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
    }

    template <class T> void read(T &x) {
        double tmp = 1;
        bool sign = false;
        x = 0;
        char ch = gc();
        for (; !isdigit(ch); ch = gc())
            if (ch == '-') sign = 1;
        for (; isdigit(ch); ch = gc())
            x = x * 10 + (ch - '0');
        if (ch == '.')
            for (ch = gc(); isdigit(ch); ch = gc())
                tmp /= 10.0, x += tmp * (ch - '0');
        if (sign) x = -x;
    }

    void read(char *s) {
        char ch = gc();
        for (; blank(ch); ch = gc())
            ;
        for (; !blank(ch); ch = gc())
            *s++ = ch;
        *s = 0;
    }

    void read(char &c) {
        for (c = gc(); blank(c); c = gc())
            ;
    }

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
        while (top)
            push(sta[--top] + '0');
    }

    template <class T> void write(T x, char lastChar) {
        write(x), push(lastChar);
    }
} io;

typedef unsigned long long ull;
const int MAXN = 5e5 + 10, b = 2e4 + 10, B = 16, K = 32, mod = (1 << 20) - 1;
int n, m, lst, a[MAXN];
ull lb[9], rb[9];

struct Node {
    int l, r;
    int mx, mn;
    ull val, tag, siz;
} t[9][b << 2];

constexpr int ls(int x) { return x << 1; }
constexpr int rs(int x) { return x << 1 | 1; }

int get_bl(int x) {
    int nw = 1;
    while (x > rb[nw])
        nw++;
    return nw;
}

void pushup(int bl, int p) {
    t[bl][p].siz = t[bl][ls(p)].siz + t[bl][rs(p)].siz;
    t[bl][p].val = t[bl][ls(p)].val + t[bl][rs(p)].val;
    t[bl][p].mn = min(t[bl][ls(p)].mn, t[bl][rs(p)].mn);
    t[bl][p].mx = max(t[bl][ls(p)].mx, t[bl][rs(p)].mx);
}

void pushdown(int bl, int p) {
    if (!t[bl][p].tag) return;
    if (t[bl][ls(p)].siz) t[bl][ls(p)].tag += t[bl][p].tag;
    if (t[bl][rs(p)].siz) t[bl][rs(p)].tag += t[bl][p].tag;
    if (t[bl][ls(p)].siz) {
        t[bl][ls(p)].val -= t[bl][p].tag * t[bl][ls(p)].siz;
        t[bl][ls(p)].mn -= t[bl][p].tag, t[bl][ls(p)].mx -= t[bl][p].tag;
    }
    if (t[bl][rs(p)].siz) {
        t[bl][rs(p)].val -= t[bl][p].tag * t[bl][rs(p)].siz;
        t[bl][rs(p)].mn -= t[bl][p].tag, t[bl][rs(p)].mx -= t[bl][p].tag;
    }
    t[bl][p].tag = 0;
}

void pushdown_bl(int bl, int L, int R, ull &x) {
    if (!x) return;
    for (int i = L; i <= R; i++)
        if (lb[bl] <= a[i] && a[i] <= rb[bl]) a[i] -= x;
    x = 0;
}

void pushup_bl(int bl, int p, int L, int R) {
    t[bl][p].siz = 0, t[bl][p].val = 0, t[bl][p].mx = 0, t[bl][p].mn = INT_MAX;
    for (int i = L; i <= R; i++) {
        if (lb[bl] <= a[i] && a[i] <= rb[bl]) {
            t[bl][p].siz++;
            t[bl][p].val += a[i];
            t[bl][p].mx = max(t[bl][p].mx, a[i]);
            t[bl][p].mn = min(t[bl][p].mn, a[i]);
        }
    }
}

void build(int bl, int p, int l, int r) {
    t[bl][p].l = l, t[bl][p].r = r, t[bl][p].mn = INT_MAX;
    if (r - l + 1 <= K) return;
    int mid = (l + r) >> 1;
    build(bl, ls(p), l, mid), build(bl, rs(p), mid + 1, r);
}

void insert(int bl, int p, int pos, int x) {
    if (t[bl][p].r - t[bl][p].l + 1 <= K) {
        pushdown_bl(bl, t[bl][p].l, t[bl][p].r, t[bl][p].tag);
        a[pos] = x;
        pushup_bl(bl, p, t[bl][p].l, t[bl][p].r);
        return;
    }

    int mid = (t[bl][p].l + t[bl][p].r) >> 1;
    pushdown(bl, p);
    if (pos <= mid) insert(bl, p << 1, pos, x);
    else insert(bl, p << 1 | 1, pos, x);
    pushup(bl, p);
}

void modify_bl(int bl, int L, int R, int x) {
    for (int i = L; i <= R; i++) {
        if (lb[bl] <= a[i] && a[i] <= rb[bl] && a[i] > x) {
            a[i] -= x;
            if (a[i] <= lb[bl]) insert(get_bl(a[i]), 1, i, a[i]);
        }
    }
}

void query_bl(int bl, int L, int R, ull &ans) {
    for (int i = L; i <= R; i++)
        if (lb[bl] <= a[i] && a[i] <= rb[bl])
            ans += a[i];
}

void modify(int bl, int p, int l, int r, int x) {
    if (t[bl][p].mx <= x) return;
    if (t[bl][p].r - t[bl][p].l + 1 <= K) {
        pushdown_bl(bl, t[bl][p].l, t[bl][p].r, t[bl][p].tag);
        l = max(l, t[bl][p].l), r = min(r, t[bl][p].r);
        modify_bl(bl, l, r, x);
        pushup_bl(bl, p, t[bl][p].l, t[bl][p].r);
        return;
    }

    if (l <= t[bl][p].l && t[bl][p].r <= r && t[bl][p].mn - x >= lb[bl]) {
        t[bl][p].val -= x * t[bl][p].siz, t[bl][p].tag += x;
        t[bl][p].mx -= x, t[bl][p].mn -= x;
        return;
    }

    int mid = (t[bl][p].l + t[bl][p].r) >> 1;
    pushdown(bl, p);
    if (l <= mid) modify(bl, ls(p), l, r, x);
    if (r > mid) modify(bl, rs(p), l, r, x);
    pushup(bl, p);
    return;
}

void query(int bl, int p, int l, int r, ull &ans) {
    if (l <= t[bl][p].l && t[bl][p].r <= r) {
        ans += t[bl][p].val;
        return;
    }

    if (t[bl][p].r - t[bl][p].l + 1 <= K) {
        pushdown_bl(bl, t[bl][p].l, t[bl][p].r, t[bl][p].tag);
        l = max(l, t[bl][p].l), r = min(r, t[bl][p].r);
        query_bl(bl, l, r, ans);
        return;
    }

    int mid = (t[bl][p].l + t[bl][p].r) >> 1;
    pushdown(bl, p);
    if (l <= mid) query(bl, ls(p), l, r, ans);
    if (r > mid) query(bl, rs(p), l, r, ans);
    pushup(bl, p);
}

signed main() {
    io.read(n), io.read(m);
    for (int i = 1; i < 9; i++) {
        lb[i] = rb[i - 1] + 1, rb[i] = lb[i] * B - 1;
        build(i, 1, 1, n);
    }
    for (int i = 1; i <= n; i++) {
        io.read(a[i]);
        insert(get_bl(a[i]), 1, i, a[i]);
    }
    while (m --> 0) {
        int op, l, r, x;
        io.read(op), io.read(l), io.read(r);
        if (op == 1) {
            io.read(x);
            l ^= lst, r ^= lst, x ^= lst;
            for (int i = 1; i < 9; i++)
                if (rb[i] >= x) modify(i, 1, l, r, x);
        } else {
            l ^= lst, r ^= lst;
            ull ans = 0;
            for (int i = 1; i < 9; i++) query(i, 1, l, r, ans);
            io.write(ans, '\n');
            lst = ans & mod;
        }
    }
    return 0;
}