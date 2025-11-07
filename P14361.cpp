#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

const int MAXN = 1e5 + 10;
int T, n, a[MAXN][4], cnt[4], ans, id[MAXN];
priority_queue<pii, vector<pii>, greater<>> q[4];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        ans = 0;
        priority_queue<pii, vector<pii>, greater<>>().swap(q[1]), cnt[1] = 0;
        priority_queue<pii, vector<pii>, greater<>>().swap(q[2]), cnt[2] = 0;
        priority_queue<pii, vector<pii>, greater<>>().swap(q[3]), cnt[3] = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i][1] >> a[i][2] >> a[i][3];
            if (a[i][1] == max({a[i][1], a[i][2], a[i][3]})) {
                ans += a[i][1], cnt[1]++, id[i] = 1;
                q[1].emplace(a[i][1] - a[i][2], i);
                q[1].emplace(a[i][1] - a[i][3], i);
            } else if (a[i][2] == max({a[i][1], a[i][2], a[i][3]})) {
                ans += a[i][2], cnt[2]++, id[i] = 2;
                q[2].emplace(a[i][2] - a[i][1], i);
                q[2].emplace(a[i][2] - a[i][3], i);
            } else if (a[i][3] == max({a[i][1], a[i][2], a[i][3]})) {
                ans += a[i][3], cnt[3]++, id[i] = 3;
                q[3].emplace(a[i][3] - a[i][2], i);
                q[3].emplace(a[i][3] - a[i][1], i);
            }
        }
        for (int i = 1; i <= 3; i++) {
            while (cnt[i] > (n >> 1)) {
                auto [val, id] = q[i].top();
                q[i].pop();
                if (::id[id] ^ i) continue;
                ans -= val, cnt[i]--, ::id[id] = -1;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}