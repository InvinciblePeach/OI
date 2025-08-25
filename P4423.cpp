#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

const int MAXN = 2e5 + 10;
int n, m, tmp[MAXN];
ld res = INFINITY;

struct Point {
    ld x, y;
    bool operator<(const Point &o) { return x < o.x; }
} p[MAXN];

template <class T> constexpr ld fpow(const T &x) { return x * x; }

ld dis(int x, int y) { return sqrt(fpow(p[x].x - p[y].x) + fpow(p[x].y - p[y].y)); }

void solve(int l, int r) {
    if (l + 1 >= r) return;
    if (l + 2 == r) return res = min(res, dis(l, r) + dis(l + 1, r) + dis(l, r - 1)), void();

    int mid = (l + r) >> 1;
    solve(l, mid), solve(mid + 1, r);
    m = 0;
    ld len = res / 2;
    for (int i = l; i <= r; i++)
        if (fabs(p[i].x - p[mid].x) <= len) tmp[++m] = i;
    sort(tmp + 1, tmp + 1 + m, [](const int &a, const int &b) -> bool { return p[a].y < p[b].y; });
    for (int l = 1, r = 1; l <= m; l++) {
        while (r <= m && fabs(p[tmp[r]].y - p[tmp[l]].y) <= len) r++;
        for (int i = l + 1; i < r; i++)
            for (int j = i + 1; j < r; j++)
                res = min(res, dis(tmp[l], tmp[i]) + dis(tmp[i], tmp[j]) + dis(tmp[l], tmp[j]));
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i].x >> p[i].y;
    sort(p + 1, p + 1 + n);
    solve(1, n);
    printf("%.6Lf\n", res);

    return 0;
}