#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 4e4 + 10, S = 1000;
int n, m, dep[MAXN], fa[MAXN][17], mxd[MAXN], col[MAXN], lst;
int tot, id[MAXN], num[MAXN], st[MAXN], tp, pre[MAXN], f[MAXN];
bitset<MAXN> app[50][50];
vector<int> g[MAXN];

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

void dfs1(int u) {
    for (int j = 1; j < 17; j++)
            fa[u][j] = fa[fa[u][j - 1]][j - 1];
    mxd[u] = dep[u];
    for (auto v : g[u]) {
        if (v == fa[u][0]) continue;
        dep[v] = dep[u] + 1, fa[v][0] = u;
        dfs1(v);
        if (mxd[v] > mxd[u]) mxd[u] = mxd[v];
    }
    if (mxd[u] - dep[u] >= S) id[u] = ++tot, mxd[u] = dep[u];
}

void dfs2(int u) {
    for (auto v : g[u]) {
        if (v == fa[u][0]) continue;
        if (id[v]) {
            int p = id[st[tp]], q = id[v];
            for (int nw = v; nw != st[tp]; nw = fa[nw][0])
                app[p][q][col[nw]] = 1;
            for (int i = 1; i < tp; i++)
                app[id[st[i]]][q] = app[id[st[i]]][p] | app[p][q];
            pre[v] = st[tp], f[v] = f[st[tp]] + 1;
            st[++tp] = v;
        }
        dfs2(v);
        if (id[v]) tp--;
    }
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    int dlt = dep[a] - dep[b];
    for (int j = 0; dlt; j++, dlt >>= 1)
        if (dlt & 1) a = fa[a][j];
    if (a == b) return a;
    for (int j = 16; ~j; j--)
        if (fa[a][j] != fa[b][j]) a = fa[a][j], b = fa[b][j];
    return fa[a][0];
}

signed main() {
    io.read(n), io.read(m);
    for (int i = 1; i <= n; i++)
        io.read(col[i]), num[i] = col[i];
    sort(num + 1, num + 1 + n);
    auto ed = unique(num + 1, num + 1 + n);
    for (int i = 1; i <= n; i++)
        col[i] = lower_bound(num + 1, ed, col[i]) - num;

    for (int i = 1, u, v; i < n; i++) {
        io.read(u), io.read(v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs1(dep[1] = 1);
    if (!id[1]) id[1] = ++tot;
    st[tp = 1] = f[1] = 1;
    dfs2(1);

    while (m --> 0) {
        static int u, v, t;
        static bitset<MAXN> ans;
        io.read(u), io.read(v);
        u ^= lst, ans.reset(), t = lca(u, v);
        ans[col[t]] = 1;
        while (u != t && !id[u]) ans[col[u]] = 1, u = fa[u][0];
        while (v != t && !id[v]) ans[col[v]] = 1, v = fa[v][0];
        if (u != t) {
            int nw = u;
            while (dep[pre[nw]] >= dep[t])
                nw = pre[nw];
            if (nw != u) ans |= app[id[nw]][id[u]];
            while (nw != t)
                ans[col[nw]] = 1, nw = fa[nw][0];
        }
        if (v != t) {
            int nw = v;
            while (dep[pre[nw]] >= dep[t])
                nw = pre[nw];
            if (nw != v) ans |= app[id[nw]][id[v]];
            while (nw != t)
                ans[col[nw]] = 1, nw = fa[nw][0];
        }
        io.write(lst = ans.count(), '\n');
    }

    return 0;
}