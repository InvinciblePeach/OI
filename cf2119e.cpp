#include <bits/stdc++.h>
#define int long long

using namespace std;
const int MAXN = 1e5 + 10, INF = (1LL << 60);
int T, n, a[MAXN], b[MAXN], c[MAXN];

int dfs(int x, int mask1, int mask0) {
    if (mask1 & mask0) return INF;
    int y = 0;
    bool tight = true;
    for (int b = 29; b >= 0; --b) {
        int xb = (x >> b) & 1;
        bool need1 = (mask1 >> b) & 1;
        bool need0 = (mask0 >> b) & 1;
        if (need1) {
            if (tight && xb == 0) tight = false;
            y |= (1LL << b);
        } else if (need0) {
            if (tight && xb == 1) {
                int candidate = INF;
                int high = (x >> (b + 1));
                ++high;
                int x2 = (high << (b + 1));
                candidate = dfs(x2, mask1, mask0);
                return candidate;
            }
        } else {
            if (tight) {
                if (xb) {
                    y |= (1LL << b);
                }
            } else {
            }
        }
    }
    if (y < x) return INF;
    return y;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n - 1; i++)
            cin >> a[i];
        for (int i = 0; i < n; i++)
            cin >> b[i];

        c[0] = b[0];
        int sum = 0;
        bool ok = true;
        for (int i = 0; i < n - 1; i++) {
            int mask1 = a[i];
            int mask0 = c[i] & (~a[i]);
            int tmp = dfs(b[i + 1], mask1, mask0);
            if (tmp == INF) {
                ok = false;
                break;
            }
            c[i + 1] = tmp;
            sum += (c[i + 1] - b[i + 1]);
            if (sum > (int)4e18) {
                ok = false;
                break;
            }
        }

        if (!ok) {
            cout << -1 << "\n";
        } else {
            cout << sum << "\n";
        }
    }
    return 0;
}
