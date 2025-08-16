#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10, mod = 998244353;
int n, m, num, tot, id[MAXN], st[MAXN], top, dep[MAXN], fa[MAXN][20];
int cnt, fr[MAXN], ed[MAXN], key[50], dp[MAXN][2], k0[MAXN][2], k1[MAXN][2];
int rev[MAXN][2], ans;
vector<int> g[MAXN], t[MAXN];
bitset<MAXN> vis;

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
    bool sign = false;
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

void dfs(int u) {
    id[u] = ++tot;
    for (int i = 1; i < 20; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];

    for (auto v : g[u]) {
        if (v == fa[u][0]) continue;
        if (!id[v]) {
            fa[v][0] = u;
            dep[v] = dep[u] + 1;
            dfs(v);
        } else
            fr[++cnt] = v, ed[cnt] = u, vis[v] = vis[u] = 1;
    }
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    int d = dep[a] - dep[b];
    for (int i = 0; d; i++, d >>= 1)
        if (d & 1) a = fa[a][i];
    if (a == b) return b;

    for (int i = 19; ~i; i--)
        if (fa[a][i] != fa[b][i]) a = fa[a][i], b = fa[b][i];
    return fa[a][0];
}

void dfs2(int u) {
    for (auto v : g[u]) {
        if (v == fa[u][0]) continue;
        dfs2(v);
        vis[u] = vis[u] | vis[v];
    }
}

void insert(int x) {
    if (!top) return st[top = 1] = 1, void();

    int tmp = lca(x, st[top]);
    if (tmp == x) return;
    while (top > 1 && dep[tmp] < dep[st[top - 1]])
        t[st[top - 1]].emplace_back(st[top]), top--;
    if (dep[tmp] < dep[st[top]]) t[tmp].emplace_back(st[top--]);
    if (!top || st[top] != tmp) st[++top] = tmp;
    st[++top] = x;
}

void build() {
    for (int i = 1; i <= cnt; i++)
        key[++num] = fr[i], key[++num] = ed[i];
    sort(key + 1, key + 1 + num,
         [](const int &a, const int &b) -> bool { return id[a] < id[b]; });
    st[top = 1] = 1;
    for (int i = 1; i <= num; i++)
        insert(key[i]);
    while (top > 1)
        t[st[top - 1]].emplace_back(st[top]), top--;
}

void solve() {
    io.read(n), io.read(m);
    for (int i = 1, u, v; i <= m; i++) {
        io.read(u), io.read(v);
        g[u].emplace_back(v), g[v].emplace_back(u);
    }
    dfs(1);
    for (int i = 0; i <= n; i++) g[i].clear();
    for (int i = 1; i <= n; i++)
        if (fa[i][0] != i) g[fa[i][0]].emplace_back(i);
    dfs2(1);
    build();
}

void pre(int u, int F) {
    dp[u][1] = dp[u][0] = 1;
    for (auto v : g[u]) {
        if (v == F || v == fa[u][0]) continue;
        pre(v, u);
        (dp[u][1] *= dp[v][0]) %= mod;
        (dp[u][0] *= dp[v][1] + dp[v][0]) %= mod;
    }
}

void get(int u, int F) {
    int v = u;
    k0[u][0] = k0[u][1] = k1[u][0] = 1;
    while (fa[v][0] != F) {
        pre(fa[v][0], v);
        int r0 = k0[u][0], r1 = k0[u][1];
        k0[u][0] = (dp[fa[v][0]][0] * r0 + dp[fa[v][0]][1] * k1[u][0]) % mod;
        k0[u][1] = (dp[fa[v][0]][0] * r1 + dp[fa[v][0]][1] * k1[u][1]) % mod;
        k1[u][1] = dp[fa[v][0]][0] * r1 % mod;
        k1[u][0] = dp[fa[v][0]][0] * r0 % mod;
        v = fa[v][0];
    }
}

void getinit(int u, int F) {
    rev[u][0] = rev[u][1] = 1;
    for (auto v : g[u]) {
        if (v == F || vis[v]) continue;
        getinit(v, u);
        (rev[u][0] *= rev[v][0] + rev[v][1]) %= mod;
        (rev[u][1] *= rev[v][0]) %= mod;
    }
}

void dfsinit(int u, int F) {
    getinit(u, F), key[++num] = u;
    if (u != F) get(u, F);
    for (auto v : t[u]) {
        if (v == F) continue;
        dfsinit(v, u);
    }
}

void DP(int u, int F) {
    for (auto v : t[u]) {
        if (v == F) continue;
        DP(v, u);
        (dp[u][0] *= k0[v][0] * dp[v][0] % mod + k0[v][1] * dp[v][1] % mod) %= mod;
        (dp[u][1] *= k1[v][0] * dp[v][0] % mod + k1[v][1] * dp[v][1] % mod) %= mod;
    }
}

signed main() {
    solve(), num = 0, dfsinit(1, 1);
    for (int st = 0; st < (1 << cnt); st++) {
        for (int j = 1; j <= num; j++)
            dp[key[j]][0] = rev[key[j]][0], dp[key[j]][1] = rev[key[j]][1];
        for (int j = 1; j <= cnt; j++) {
            if ((1 << (j - 1)) & st) dp[fr[j]][0] = dp[ed[j]][1] = 0;
            else dp[fr[j]][1] = 0;
        }
        DP(1, 1), (ans += dp[1][0] + dp[1][1]) %= mod;
    }
    io.write(ans, '\n');

    return 0;
}