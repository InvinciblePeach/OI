#include <bits/stdc++.h>
#define lc(x) x << 1
#define rc(x) x << 1 | 1

// #define DEBUG 1  // 调试开关
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
#if DEBUG  // 调试，可显示字符
		return getchar();
#endif
		if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin);
		return p1 == p2 ? ' ' : *p1++;
	}

	bool blank(char ch) {
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}

	template <class T>
		void read(T &x) {
			double tmp = 1;
			bool sign = 0;
			x = 0;
			char ch = gc();
			for (; !isdigit(ch); ch = gc())
				if (ch == '-') sign = 1;
			for (; isdigit(ch); ch = gc()) x = x * 10 + (ch - '0');
			if (ch == '.')
				for (ch = gc(); isdigit(ch); ch = gc())
					tmp /= 10.0, x += tmp * (ch - '0');
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
#if DEBUG  // 调试，可显示字符
		putchar(c);
#else
		if (pp - pbuf == MAXSIZE) fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
		*pp++ = c;
#endif
	}

	template <class T>
		void write(T x) {
			if (x < 0) x = -x, push('-');  // 负数输出
			static T sta[35];
			T top = 0;
			do {
				sta[top++] = x % 10, x /= 10;
			} while (x);
			while (top) push(sta[--top] + '0');
		}

	template <class T>
		void write(T x, char lastChar) {
			write(x), push(lastChar);
		}
} io;

using namespace std;
typedef long long ll;

const int MAXN = 1e6 + 10, INF = 0x3f3f3f3f;
int n, m, v[MAXN], fa[MAXN], siz[MAXN], son[MAXN];
int tot, top[MAXN], ed[MAXN], dfn[MAXN], id[MAXN];
int f[MAXN][2], lst;
vector<int> g[MAXN];

struct Matrix {
    int a[2][2];

    Matrix() {
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                a[i][j] = -INF;
    }

    constexpr int *operator[](const int &x) { return a[x]; }

    void init() { a[0][0] = a[1][1] = 0; }

    Matrix operator*(const Matrix &o) {
        Matrix res;
        for (int i = 0; i < 2; i++)
            for (int k = 0; k < 2; k++)
                for (int j = 0; j < 2; j++)
                    res[i][j] = max(res[i][j], a[i][k] + o.a[k][j]);
        return res;
    }
} val[MAXN];

void dfs1(int u) {
    siz[u] = 1;
    for (auto v : g[u]) {
        if (v == fa[u]) continue;
        fa[v] = u, dfs1(v);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int top) {
    dfn[id[u] = ++tot] = u;
    ::top[u] = top, ed[top] = max(ed[top], tot);

    f[u][0] = 0, f[u][1] = v[u];
    val[u][0][0] = val[u][0][1] = 0;
    val[u][1][0] = v[u];
    if (son[u]) {
        dfs2(son[u], top);
        f[u][0] += max(f[son[u]][0], f[son[u]][1]);
        f[u][1] += f[son[u]][0];
    }

    for (auto v : g[u]) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
        f[u][0] += max(f[v][0], f[v][1]);
        f[u][1] += f[v][0];
        val[u][0][1] = (val[u][0][0] += max(f[v][0], f[v][1]));
        val[u][1][0] += f[v][0];
    }

}

struct Node {
    int l, r;
    Matrix tag;
} t[MAXN << 2];

void pushup(int p) { t[p].tag = t[lc(p)].tag * t[rc(p)].tag; }

void build(int p, int l, int r) {
    t[p] = {l, r, Matrix()};
    if (l == r) return t[p].tag = val[dfn[l]], void();

    int mid = (l + r) >> 1;
    build(lc(p), l, mid), build(rc(p), mid + 1, r);
    pushup(p);
}

void modify(int p, int x) {
    if (t[p].l == t[p].r) return t[p].tag = val[dfn[x]], void();

    if (x <= t[lc(p)].r) modify(lc(p), x);
    else modify(rc(p), x);
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

void update(int u, int w) {
    val[u][1][0] += w - v[u];
    v[u] = w;

    static Matrix bef, aft;
    while (u) {
        bef = query(1, id[top[u]], ed[top[u]]);
        modify(1, id[u]);
        aft = query(1, id[top[u]], ed[top[u]]);

        u = fa[top[u]];
        val[u][0][1] = (val[u][0][0] += max(aft[0][0], aft[1][0]) - max(bef[0][0], bef[1][0]));
        val[u][1][0] += aft[0][0] - bef[0][0];
    }
}

signed main() {
    io.read(n), io.read(m);
    for (int i = 1; i <= n; i++) io.read(v[i]);
    for (int i = 1, u, v; i < n; i++) {
        io.read(u), io.read(v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs1(1), dfs2(1, 1);
    assert(n == tot);
    build(1, 1, n);
    
    while (m --> 0) {
        static int u, w;
        io.read(u), io.read(w);
        u ^= lst;
        update(u, w);
        auto ans = query(1, id[1], ed[1]);
        io.write(lst = max(ans[0][0], ans[1][0]), '\n');
    }

    return 0;
}