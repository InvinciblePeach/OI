#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 5e5 + 10;
int n, m, fa[MAXN], siz[MAXN], tim[MAXN], ans, cnt;

int get(int x) {
    while (fa[x] ^ x) x = fa[x];
    return x;
}

void merge(int x, int y, int tim) {
    int fax = get(x), fay = get(y);
    if (fax == fay) return;
    if (siz[fax] > siz[fay]) swap(fax, fay);
    fa[fax] = fay, siz[fay] += siz[fax], ::tim[fax] = tim;
}

int getans(int x, int y) {
    if (get(x) ^ get(y)) return 0;
    int res = 0;
    auto [depx, depy] = pair(0, 0);
    auto [u, v] = pair(x, y);
    while (fa[u] ^ u) u = fa[u], depx++;
    while (fa[v] ^ v) v = fa[v], depy++;
    while (depx > depy) res = max(res, tim[x]), x = fa[x], depx--;
    while (depy > depx) res = max(res, tim[y]), y = fa[y], depy--;
    while (x ^ y) res = max({res, tim[x], tim[y]}), x = fa[x], y = fa[y];
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
    while (m --> 0) {
        static int op, u, v;
        cin >> op >> u >> v;
        u ^= ans, v ^= ans;
        if (op == 0) merge(u, v, ++cnt);
        else if (op == 1) cout << (ans = getans(u, v)) << '\n';
    }

    return 0;
}