#include <bits/stdc++.h>
#define int long long

using namespace std;
using pii = pair<int, int>;

const int MAXN = 1e4 + 50, MAXM = 1e6 + 50;
int n, m, k, cnt, fa[MAXN], siz[MAXN], c[15], ans;
struct Edge {
    int u, v, w;
    bool operator<(const Edge &o) const { return w < o.w; }
} e[MAXM], e1[MAXN], e2[MAXM], e3[15][MAXN];

int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }

void merge(int x, int y) {
    x = get(x), y = get(y);
    if (siz[x] > siz[y]) swap(x, y);
    siz[y] += siz[x], fa[x] = y;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
        cin >> e[i].u >> e[i].v >> e[i].w;
    }
    for (int i = 1; i <= k; i++) {
        cin >> c[i];
        for (int j = 1, w; j <= n; j++) cin >> w, e3[i][j] = {n + i, j, w};
        sort(e3[i] + 1, e3[i] + 1 + n);
    }
    for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
    sort(e + 1, e + 1 + m);
    for (int i = 1; i <= m; i++) {
        auto [u, v, w] = e[i];
        if (get(u) == get(v)) continue;
        ans += w;
        e1[++cnt] = e[i];
        merge(u, v);
    }
    for (int st = 1; st < (1 << k); st++) {
        int res = 0, nw = n - 1;
        memcpy(e2 + 1, e1 + 1, sizeof(Edge) * (n - 1));
        for (int i = 1; i <= k; i++) {
            if (st >> (i - 1) & 1) {
                res += c[i];
                memcpy(e2 + 1 + nw, e3[i] + 1, sizeof(Edge) * n);
                inplace_merge(e2 + 1, e2 + 1 + nw, e2 + 1 + nw + n);
                nw += n;
            }
        }
        for (int i = 1; i <= n + k; i++) fa[i] = i, siz[i] = 1;
        for (int i = 1; i <= nw; i++) {
            auto [u, v, w] = e2[i];
            if (get(u) == get(v)) continue;
            res += w;
            merge(u, v);
        }
        ans = min(res, ans);
    }
    cout << ans << '\n';

    return 0;
}