#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e6 + 10;
int n, m, lx, ly, rx, ry, t[MAXN], ans[MAXN];

constexpr int lowbit(int x) { return x & -x; }

void add(int x, int val) {
    for (; x < MAXN; x += lowbit(x))
        t[x] = max(t[x], val);
}

void clean(int x) {
    for (; x < MAXN; x += lowbit(x))
        if (t[x]) t[x] = 0;
        else break;
}

int ask(int x) {
    int res = 0;
    for (; x; x -= lowbit(x))
        res = max(res, t[x]);
    return res;
}

struct Query {
    int x, y, t;
    bool flag;

    Query() {}
    Query(int X, int Y, int T, bool Flag) : x(X), y(Y), t(T), flag(Flag) {}

    bool operator<(const Query &o) const { return x == o.x ? y < o.y : x < o.x; }
} q[MAXN], p[MAXN], a[MAXN];

void solve(int l, int r) {
    if (l >= r) return;
    int mid = (l + r) >> 1;
    solve(l, mid), solve(mid + 1, r);;

    int j = l;
    for (int i = mid + 1; i <= r; i++) {
        if (!p[i].flag) {
            for (; j <= mid && p[j].x <= p[i].x; j++)
                if (p[j].flag) add(p[j].y, p[j].x + p[j].y);
            int tmp = ask(p[i].y);
            if (tmp) ans[p[i].t] = min(ans[p[i].t], p[i].x + p[i].y - tmp);
        }
    }
    for (int i = l; i < j; i++)
        if (p[i].flag) clean(p[i].y);
    sort(p + l, p + r + 1);
}

void del() {
    rx = ry = m = 0;
    for (int i = 1; i <= n; i++)
        if (!p[i].flag) rx = max(rx, p[i].x), ry = max(ry, p[i].y);
    for (int i = 1; i <= n; i++)
        if (p[i].x <= rx && p[i].y <= ry) q[++m] = p[i];
    memcpy(p + 1, q + 1, m * sizeof(Query));
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> p[i].x >> p[i].y;
        p[i].x++, p[i].y++;
        p[i].t = i, p[i].flag = true;
        lx = max(lx, p[i].x), ly = max(ly, p[i].y);
    }
    while (m --> 0) {
        static int k, x, y;
        cin >> k >> x >> y;
        n++, x++, y++;
        p[n] = {x, y, n, k & 1};
        lx = max(lx, p[n].x), ly = max(ly, p[n].y);
    }
    memcpy(a + 1, p + 1, n * sizeof(Query));
    memset(ans + 1, 0x3f, n << 2), lx++, ly++;

    del(), solve(1, m);

    for (int i = 1; i <= n; ++i)
        p[i] = a[i], p[i].x = lx - p[i].x;
    del(), solve(1, m);

    for (int i = 1; i <= n; ++i)
        p[i] = a[i], p[i].y = ly - p[i].y;
    del(), solve(1, m);

    for (int i = 1; i <= n; ++i)
        p[i] = a[i], p[i].x = lx - p[i].x, p[i].y = ly - p[i].y;
    del(), solve(1, m);

    for (int i = 1; i <= n; i++)
        if (!a[i].flag) cout << ans[i] << '\n';

    return 0;
}