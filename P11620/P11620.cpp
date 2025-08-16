#include <bits/stdc++.h>

using namespace std;

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
const int MAXN = 1e5 + 10, MAXV = 47;
int n, q, a[MAXN];
bitset<MAXN> vis[MAXV];

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

struct Fenwick {
    int t[MAXN];

    constexpr int lowbit(const int &x) { return x & -x; }

    void add(int x, int val) {
        for (; x <= n; x += lowbit(x)) t[x] ^= val;
    }

    int query(int x) {
        int res = 0;
        for (; x; x -= lowbit(x)) res ^= t[x];
        return res;
    }

    int query(int l, int r) { return query(r) ^ query(l - 1); }
} val, b[MAXV];

struct LB {
    int a[32];

    void clear() { memset(a, 0, sizeof(a)); }

    void insert(int x) {
        for (int i = 31; ~i; i--) {
            if (x >> i & 1) {
                if (!a[i]) {
                    a[i] = x;
                    break;
                }
                x ^= a[i];
            }
        }
    }

    int query(int val) {
        for (int i = 31; ~i; i--) {
            val = max(val, val ^ a[i]);
        }
        return val;
    }
} ans;

signed main() {
    read(n), read(q);
    for (int i = 1; i <= n; i++) read(a[i]);
    for (int i = 1, t; i <= n; i++) {
        t = a[i - 1] ^ a[i];
        for (int j = 0; j < MAXV; j++)
            if (vis[j][i] = (rnd() & 1)) b[j].add(i, t);
        val.add(i, t);
    }
    while (q-- > 0) {
        static int op, l, r, v;
        read(op), read(l), read(r), read(v);
        if (op == 1) {
            val.add(l, v), val.add(r + 1, v);
            for (int i = 0; i < MAXV; i++) {
                if (vis[i][l]) b[i].add(l, v);
                if (r + 1 <= n && vis[i][r + 1]) b[i].add(r + 1, v);
            }
        } else {
            ans.clear();
            for (int i = 0; i < MAXV; i++) ans.insert(b[i].query(l + 1, r));
            ans.insert(val.query(l));
            print(ans.query(v)), pc('\n');
        }
    }
    flush();
}