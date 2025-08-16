#include <bits/stdc++.h>
// #define DEBUG 1  // 调试开关

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

typedef long long ll;
typedef pair<int, int> pii;
const int MAXN = 1e5 + 10, S = 600;
int n, m, s, a[MAXN], w[MAXN], id[MAXN], x[MAXN], y[MAXN], L[S], R[S];
ll ans, pre[MAXN], suf[MAXN], f[S][S], cnt[S][MAXN], t[MAXN];
pii b[MAXN];

constexpr int lowbit(int x) { return x & -x; }

void add(int x, int val) {
    for (; x <= n; x += lowbit(x))
        t[x] += val;
}

ll query(int x) {
    ll res = 0;
    for (; x; x -= lowbit(x))
        res += t[x];
    return res;
}

int merge(const int *x, const int *y, int lenx, int leny) {
    int i = 1, j = 1, res = 0;
    while (i <= lenx && j <= leny)
        if (x[i] < y[j]) i++;
        else res += lenx - i + 1, j++;
    return res;
}

signed main() {
    io.read(n), io.read(m);
    for (int i = 1; i <= n; i++) {
        io.read(a[i]);
        b[i] = {a[i], i};
    }

    s = (n - 1) / S + 1;
    for (int i = 1; i <= s; i++) L[i] = R[i - 1] + 1, R[i] = i * S;
    R[s] = n;

    for (int i = 1; i <= s; i++) {
        sort(b + L[i], b + 1 + R[i]);
        for (int j = L[i]; j <= R[i]; j++)
            w[j] = b[j].first, id[j] = b[j].second;
        ll x = 0;
        for (int j = L[i]; j <= R[i]; j++) {
            add(a[j], 1);
            x += query(n) - query(a[j]);
            pre[j] = x;
        }
        f[i][i] = x;
        for (int j = L[i]; j <= R[i]; j++) {
            suf[j] = x;
            add(a[j], -1);
            x -= query(a[j] - 1);
        }
    }

    sort(b + 1, b + 1 + n);
    for (int i = 1; i <= s; i++) {
        for (int j = 1, k = L[i]; j <= n; j++) {
            int val = b[j].first, idx = b[j].second;
            while (k <= R[i] && val > w[k]) k++;
            if (idx < L[i]) cnt[i][idx] = k - L[i];
            else if (idx > R[i])
                cnt[i][idx] = R[i] - k + 1 - (k <= R[i] && val == w[k]);
        }
    }

    for (int i = 1; i <= s; i++)
        for (int j = 2; j <= n; j++)
            cnt[i][j] += cnt[i][j - 1];

    for (int len = 1; len <= s; len++) {
        for (int i = 1; i + len <= s; i++) {
            int j = i + len;
            f[i][j] = f[i][j - 1] + f[i + 1][j] - f[i + 1][j - 1] +
                      cnt[j][R[i]] - cnt[j][L[i] - 1];
        }
    }

    while (m --> 0) {
        ll l_, r_;
        io.read(l_), io.read(r_);
        const int l = l_ ^ ans, r = r_ ^ ans;
        const int Bl = (l - 1) / S + 1, Br = (r - 1) / S + 1;
        int lenx = 0, leny = 0;
        if (Bl == Br) {
            for (int i = L[Bl]; i <= R[Bl]; i++) {
                if (l <= id[i] && id[i] <= r) y[++leny] = w[i];
                else if (id[i] < l) x[++lenx] = w[i];
            }
            ans = pre[r] - (l != L[Bl]) * pre[l - 1] - merge(x, y, lenx, leny);
        } else {
            ans = f[Bl + 1][Br - 1] + suf[l] + pre[r];
            for (int i = Bl + 1; i < Br; i++)
                ans += (cnt[i][R[Bl]] - cnt[i][l - 1]) +
                       (cnt[i][r] - cnt[i][L[Br] - 1]);
            for (int i = L[Bl]; i <= R[Bl]; i++)
                if (l <= id[i]) x[++lenx] = w[i];
            for (int i = L[Br]; i <= R[Br]; i++)
                if (id[i] <= r) y[++leny] = w[i];
            ans += merge(x, y, lenx, leny);
        }
        io.write(ans, '\n');
    }
    return 0;
}