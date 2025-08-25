#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 5e5 + 10;
int n, m, tim[MAXN], a[MAXN], d[25], ans[MAXN];

struct Query {
    int l, r, id;

    bool operator<(const Query &o) const { return r < o.r; }
} q[MAXN];

void insert(int nw, int x) {
    for (int i = 20; ~i; i--) {
        if (!(x >> i & 1)) continue;
        if (tim[i] < nw) swap(tim[i], nw), swap(x, d[i]);
        if (!nw) break;
        x ^= d[i];
    }
}

int query(int nw) {
    int res = 0;
    for (int i = 20; ~i; i--)
        if (tim[i] >= nw && !(res >> i & 1)) res ^= d[i];
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> m;
    for (int i = 1; i <= m; i++) cin >> q[i].l >> q[i].r, q[i].id = i;
    sort(q + 1, q + 1 + m);

    for (int i = 1, j = 1; i <= m; i++) {
        for (; j <= q[i].r; j++) insert(j, a[j]);
        ans[q[i].id] = query(q[i].l);
    }
    for (int i = 1; i <= m; i++) cout << ans[i] << '\n';

    return 0;
}