#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;
int n, d, m, dfn[MAXN], low[MAXN], scc[MAXN], st[MAXN], pos[MAXN], tot, cnt, top;
char s[MAXN];
bitset<MAXN> vis;
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

struct Node {
    int a, b;
    char x, y;
} e[MAXN];

constexpr int change(int p, char c) {
    if (s[p] == 'a') return c == 'B' ? p : p + n;
    if (s[p] == 'b' || s[p] == 'c') return c == 'A' ? p : p + n;
}

void tarjan(int u) {
    vis[u] = 1;
    dfn[u] = low[u] = ++tot;
    st[++top] = u;
    for (auto v : g[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        vis[u] = 0, scc[u] = ++cnt;
        while (st[top] != u) vis[st[top]] = 0, scc[st[top]] = cnt, top--;
        top--;
    }
}

void solve() {
    memset(dfn + 1, 0, n << 3);
    memset(low + 1, 0, n << 3);
    memset(scc + 1, 0, n << 3);
    tot = cnt = 0;
    for (int i = 1; i <= (n << 1); i++) g[i].clear();
    for (int i = 1; i <= m; i++) {
        auto [a, b, x, y] = e[i];
        if (x == s[a] - 32) continue;
        int u1 = change(a, x), u2 = (u1 > n ? u1 - n : u1 + n);
        if (y == s[b] - 32) {
            g[u1].emplace_back(u2);
            continue;
        }
        int v1 = change(b, y), v2 = (v1 > n ? v1 - n : v1 + n);
        g[u1].emplace_back(v1), g[v2].emplace_back(u2);
    }
    for (int i = 1; i <= (n << 1); i++)
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n; i++)
        if (scc[i] == scc[i + n]) return;
    for (int i = 1; i <= n; i++) {
        if (s[i] == 'a') io.push(scc[i] < scc[i + n] ? 'B' : 'C');
        else if (s[i] == 'b') io.push(scc[i] < scc[i + n] ? 'A' : 'C');
        else if (s[i] == 'c') io.push(scc[i] < scc[i + n] ? 'A' : 'B');
    }
    exit(0);
}

void dfs(int id) {
    if (id == d) return solve();
    s[pos[id]] = 'a', dfs(id + 1);
    s[pos[id]] = 'b', dfs(id + 1);
}

signed main() {
    io.read(n), io.read(d);
    d = 0;
    for (int i = 1; i <= n; i++) {
        io.read(s[i]);
        if (s[i] == 'x') pos[d++] = i;
    }
    io.read(m);
    for (int i = 1; i <= m; i++)
        io.read(e[i].a), io.read(e[i].x), io.read(e[i].b), io.read(e[i].y);
    dfs(0);
    io.write(-1, '\n');

    return 0;
}