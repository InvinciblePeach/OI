#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
const int MAXN = 5e4 + 10;
int n, k, a[MAXN][4], mx[4], mn[4];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int T;
    cin >> T >> k;
    while (T-- > 0) {
        cin >> n;
        for (int i = 0; i < k; i++)
            for (int j = 1; j <= n; j++) cin >> a[j][i];
        int ans = INT_MAX;
        for (int _ = 1; _ <= 10; _++) {
            shuffle(a + 1, a + 1 + n, rnd);
            memset(mx, 0, sizeof(mx)), memset(mn, 0x3f, sizeof(mn));
            int res = 0;
            for (int i = 1; i <= n; i++) {
                static int tmp[4];
                memset(tmp, 0, sizeof(tmp));
                for (int j = 0; j < k; j++)
                    for (int p = 0; p < k; p++)
                        tmp[j] = max(tmp[j], max(mx[p], a[i][(j + p) % k]) - min(mn[p], a[i][(j + p) % k]));
                int nw = *min_element(tmp, tmp + k);
                for (int j = 0; j < k; j++) {
                    if (tmp[j] == nw) {
                        res = nw;
                        for (int p = 0; p < k; p++)
                            mx[p] = max(mx[p], a[i][(j + p) % k]), mn[p] = min(mn[p], a[i][(j + p) % k]);
                        break;
                    }
                }
            }
            ans = min(ans, res);
        }
        cout << ans << '\n';
    }

    return 0;
}