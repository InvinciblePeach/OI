#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 3e5 + 10;

int n, m, ans[MAXN], high[MAXN], fa[MAXN], h[MAXN], a[MAXN], v[MAXN], c[MAXN], rt[MAXN];
int die[MAXN];
struct Node {
    int lc, rc, dep;
    int sum, add, mul;
} t[MAXN];

void pushdown(int p) {
    if (!t[p].add && t[p].mul == 1) return;
    if (t[p].lc) {
        t[t[p].lc].mul *= t[p].mul;
        t[t[p].lc].add *= t[p].mul;
        t[t[p].lc].add += t[p].add;
        t[t[p].lc].sum *= t[p].mul;
        t[t[p].lc].sum += t[p].add;
    }
    if (t[p].rc) {
        t[t[p].rc].mul *= t[p].mul;
        t[t[p].rc].add *= t[p].mul;
        t[t[p].rc].add += t[p].add;
        t[t[p].rc].sum *= t[p].mul;
        t[t[p].rc].sum += t[p].add;
    }
    t[p].add = 0, t[p].mul = 1;
}

int merge(int x, int y) {
    if (!x || !y) return x | y;
    pushdown(x), pushdown(y);
    if (t[x].sum > t[y].sum) swap(x, y);
    t[x].rc = merge(t[x].rc, y);
    if (t[t[x].lc].dep < t[t[x].rc].dep) swap(t[x].lc, t[x].rc);
    t[x].dep = t[t[x].rc].dep + 1;
    return x;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> h[i];
    t[0].dep = -1;
    high[1] = 1;
    for (int i = 2; i <= n; i++) {
        cin >> fa[i] >> a[i] >> v[i];
        high[i] = high[fa[i]] + 1;
    }
    for (int i = 1; i <= m; i++) {
        cin >> t[i].sum >> c[i];
        t[i].mul = 1;
        if (!rt[c[i]]) rt[c[i]] = i;
        else rt[c[i]] = merge(rt[c[i]], i);
    }
    for (int i = n; i; i--) {
        while (rt[i]) {
            if (t[rt[i]].sum < h[i]) {
                die[rt[i]] = i;
                pushdown(rt[i]);
                if (!t[rt[i]].lc) rt[i] = 0;
                else rt[i] = merge(t[rt[i]].lc, t[rt[i]].rc);
            } else break;
        }
        if (i == 1) break;
        if (!rt[i]) continue;
        if (a[i]) t[rt[i]].mul *= v[i], t[rt[i]].add *= v[i], t[rt[i]].sum *= v[i];
        else t[rt[i]].add += v[i], t[rt[i]].sum += v[i];
        pushdown(rt[i]);
        if (!rt[fa[i]]) rt[fa[i]] = rt[i];
        else rt[fa[i]] = merge(rt[fa[i]], rt[i]);
    }
    for (int i = 1; i <= m; i++) ans[die[i]]++;
    for (int i = 1; i <= n; i++) cout << ans[i] << '\n';
    for (int i = 1; i <= m; i++) cout << high[c[i]] - high[die[i]] << '\n';
    return 0;
}