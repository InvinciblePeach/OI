#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int T, n, k, q, p[MAXN], d[MAXN], ans[MAXN];

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

void solve() {
    map<int, int> mp;
    map<int, vector<int>> mpl, mpr;
    map<pair<int, int>, bool> dp;
    io.read(n), io.read(k);
    for (int i = 1; i <= n; i++) io.read(p[i]);
    for (int i = 1; i <= n; i++) io.read(d[i]);
    for (int i = 1; i <= n; i++) {
        mp[p[i]] = d[i];
        mpl[(d[i] + p[i]) % k].emplace_back(p[i]);
        mpr[(((d[i] - p[i]) % k) + k) % k].emplace_back(p[i]);
    }

    auto calcl = [&](int pos, int t) -> int {
        int val = (t + pos) % k;
        auto &vec = mpl[val];
        auto it = lower_bound(vec.begin(), vec.end(), pos);
        if (it == vec.begin()) return -1;
        it--;
        return *it;
    };

    auto calcr = [&](int pos, int t) -> int {
        int val = (((t - pos) % k) + k) % k;
        auto &vec = mpr[val];
        auto it = lower_bound(vec.begin(), vec.end(), pos + 1);
        if (it == vec.end()) return -1;
        return *it;
    };

    io.read(q);
    while (q --> 0) {
        static int x, d, t;
        set<pair<int, int>> st;
        io.read(x);
        d = 1, t = 0;
        bool res = false;
        if (mp.count(x) && !mp[x]) d ^= 1;

        for (int _ = 1; _ <= (n << 1); _++) {
            int y = d ? calcr(x, t) : calcl(x, t);
            if (y == -1) {
                res = true;
                break;
            } else {
                t += abs(y - x);
                x = y, d ^= 1;
            }

            if (!st.emplace(x, d).second) break;
            if (dp.count({x, d})) {
                res = dp[{x, d}];
                break;
            }
        }

        for (auto p : st) dp[p] = res;

        puts(res ? "YES" : "NO");
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    io.read(T);
    while (T --> 0) solve();

    return 0;
}