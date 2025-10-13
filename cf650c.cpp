#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e6 + 10;
int n, m, a[MAXN], idx[MAXN], idy[MAXN], ans[MAXN];

int id(int x, int y) { return (x - 1) * m + y; }

struct Node {
    int x, y;
    bool operator<(const Node &o) const { return a[id(x, y)] < a[id(o.x, o.y)]; }
} pnt[MAXN];

int fa[MAXN];

int get(int x) {
    if (fa[x] == x) return x;
    return fa[x] = get(fa[x]);
}

void merge(int x, int y) { fa[get(x)] = get(y); }

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n * m; i++) fa[i] = i;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[id(i, j)];
            pnt[id(i, j)] = {i, j};
        }
    }
    sort(pnt + 1, pnt + n * m + 1);
    for (int i = 1; i <= n * m; i++) {
        auto [x, y] = pnt[i];
        int fax = get(idx[x]), fay = get(idy[y]), fap = get(id(x, y));
        if (a[fap] == a[fax]) fa[fax] = fap;
        if (a[fap] == a[fay]) fa[fay] = fap;
        idx[x] = idy[y] = fap;
        ans[fap] = max(ans[fax] + (a[fap] != a[fax]), ans[fay] + (a[fap] != a[fay]));
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cout << ans[get(id(i, j))] << " \n"[j == m];

    return 0;
}