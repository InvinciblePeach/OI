#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 4e5 + 10;
mt19937 rnd(clock());
int n, theta;
double w, v;
ll ans = LLONG_MAX;
struct Point {
	ll x, y;
	double nx, ny;

    bool operator<(const Point &o) const { return nx * ny < o.nx * o.ny; }
} p[MAXN];

constexpr long long dis(const Point &i, const Point &j) {
    return (i.x - j.x) * (i.x - j.x) + (i.y - j.y) * (i.y - j.y);
}

constexpr long long mn(const ll &i, const ll &j) { return (i < j) ? i : j; }

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

signed main() {
	io.read(n);
	theta = rnd();
	w = sin(theta), v = cos(theta);
	for (int i = 1, x, y; i <= n; i ++) {
		io.read(p[i].x);
		io.read(p[i].y);
		p[i].nx = p[i].x * v - p[i].y * w;
		p[i].ny = p[i].y * v + p[i].x * w;
	}
	sort(p + 1, p + 1 + n);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n && j <= i + 600; j++)
            ans = mn(ans, dis(p[i], p[j]));
    io.write(ans);
	return 0;
}
