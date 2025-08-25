#include <iostream>
#define N 100005
int n, m, a[N], l2[N], mn[N][20];
void init() {
    for (int i = 2; i <= n; i++)
        l2[i] = l2[i >> 1] + 1;
    for (int i = 1; i <= n; i++)
        mn[i][0] = a[i];
    for (int i = 1; i <= l2[n]; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            mn[j][i] = std::min(mn[j][i - 1], mn[j + (1 << i - 1)][i - 1]);
}
int qmin(int x, int y) {
    int d = l2[y - x + 1];
    return std::min(mn[x][d], mn[y - (1 << d) + 1][d]);
}
int bs(int x, int l, int r) {
    if (qmin(l, r) > x) return 0;
    int ret = 0;
    while (l <= r) {
        int mid = l + r >> 1;
        if (qmin(l, mid) <= x)
            r = mid - 1, ret = mid;
        else
            l = mid + 1;
    }
    return ret;
}
signed main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int T;
    std::cin >> T;
    while (T--) {
        std::cin >> n;
        for (int i = 1; i <= n; i++)
            std::cin >> a[i];
        init();
        std::cin >> m;
        for (int i = 1, l, r; i <= m; i++) {
            std::cin >> l >> r;
            if (l == r) {
                std::cout << a[l] << '\n';
                continue;
            }
            int ans = a[l];
            l++;
            while (l <= r) {
                int t = bs(ans, l, r);
                if (!t) break;
                ans %= a[t], l = t + 1;
                if (!ans) break;
            }
            std::cout << ans << '\n';
        }
    }
}