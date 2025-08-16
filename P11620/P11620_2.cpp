#include <bits/stdc++.h>

using namespace std;

namespace IO {
    const int BUF = 1 << 21;
    char buff[BUF], *p1 = buff, *p2 = buff;
#define gc() (p1 == p2 && (p2 = ((p1 = buff) + fread(buff, 1, BUF, stdin)), p1 == p2) ? EOF : *p1++)
    template <typename T> inline void read(T &x) {
        char ch = gc();
        x = 0;
        int f = 1;
        while (!isdigit(ch)) {
            if (ch == '-') f = -1;
            ch = gc();
        }
        while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc();
        x *= f;
    }
    char obuf[BUF], *p3 = obuf;
    inline void pc(char ch) {
        if (p3 - obuf < BUF)
            *p3++ = ch;
        else
            fwrite(obuf, p3 - obuf, 1, stdout), p3 = obuf, *p3++ = ch;
    }
    inline void put(const char *s) {
        while (*s) pc(*s), ++s;
    }
    char ch[32], ctop;
    template <typename T> inline void print(T x) {
        if (x < 0) x = ~x + 1, pc('-');
        if (!x) return pc(48);
        while (x) ch[++ctop] = x % 10 ^ 48, x /= 10;
        while (ctop) pc(ch[ctop--]);
    }
    inline void flush() {
        fwrite(obuf, p3 - obuf, 1, stdout);
        p3 = obuf;
    }
} // namespace IO
using namespace IO;

const int N = 1e5 + 5;
int n, m, op, l, r, v, a[N];

struct Tree {
    int a[30], cnt;
    inline void ins(int x) {
        while (x && cnt < 30) {
            int i = __lg(x);
            if (!a[i]) return a[i] = x, ++cnt, void();
            x ^= a[i];
        }
    }
    inline Tree friend operator+(Tree x, Tree y) {
        // if (x.cnt < y.cnt) swap(x, y);
        for (int i = 0; i < 30 && x.cnt < 30; ++i)
            if (y.a[i]) x.ins(y.a[i]);
        return x;
    }
} t[N << 2];

#define mid ((l + r) >> 1)
#define ls 2 * p, l, mid
#define rs 2 * p + 1, mid + 1, r

void build(int p, int l, int r) {
    if (l == r) return t[p].ins(a[l]), void();
    build(ls), build(rs);
    t[p] = t[2 * p] + t[2 * p + 1];
}

void change(int p, int l, int r, int x) {
    if (l == r) {
        for (int i = 0; i < 30; ++i) t[p].a[i] = 0;
        t[p].cnt = 0;
        t[p].ins(a[x]);
        return;
    }
    if (x <= mid)
        change(ls, x);
    else
        change(rs, x);
    t[p] = t[2 * p] + t[2 * p + 1];
}
Tree ans;

void query(int p, int l, int r, int lt, int rt) {
    // if (ans.cnt == 30) return;
    if (lt <= l && r <= rt) return ans = ans + t[p], void();
    if (lt <= mid) query(ls, lt, rt);
    if (mid < rt) query(rs, lt, rt);
}

struct bit_tree {
    int t[N];
    inline void add(int x, int y) {
        for (; x <= n; x += x & -x) t[x] ^= y;
    }
    inline int query(int x) {
        int ans = 0;
        for (; x; x -= x & -x) ans ^= t[x];
        return ans;
    }
} T;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = n; i; --i) T.add(i, a[i] ^= a[i - 1]);
    build(1, 1, n);
    while (m--) {
        cin >> op >> l >> r >> v;
        if (op == 1) {
            a[l] ^= v, change(1, 1, n, l), T.add(l, v);
            if (r < n) a[r + 1] ^= v, change(1, 1, n, r + 1), T.add(r + 1, v);
        } else {
            for (int i = 0; i < 30; ++i) ans.a[i] = 0;
            ans.cnt = 0;
            ans.ins(T.query(l));
            if (l < r) query(1, 1, n, l + 1, r);
            int val = 0, res = 0;
            for (int i = 29; ~i; --i)
                if (ans.a[i] && !(((val ^ v) >> i) & 1)) val ^= ans.a[i];
            cout << (val ^ v) << '\n';
        }
    }
    flush();
    return 0;
}