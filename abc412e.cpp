#include <bits/stdc++.h>
#define int __int128

using namespace std;

const int MAXN = 1e7 + 10;
int m, L, R, cnt = 0;
bitset<MAXN> p, q;
vector<int> prime;

#define DEBUG 1  // 调试开关
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
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    io.read(L), io.read(R);
    m = sqrt((long long)R) + 1;
    for (int i = 2; i <= m; i++) {
        if (!q[i]) prime.emplace_back(i);

        for (auto j : prime) {
            if (j * i > m) break;
            q[i * j] = 1;
            if (!(i % j)) break;
        }
    }

    for (auto i : prime)
        for (int j = (L / i + 1) * i; j <= R; j += i) {
            if (p[j - L]) continue;
            p[j - L] = 1;
            int y = j;
            while (!(y % i)) y /= i;
            if (y == 1) cnt++;
        }

    for (int i = 0; i <= R - L; i++) cnt += (p[i] == 0);

    io.write(cnt, '\n');

    return 0;
}