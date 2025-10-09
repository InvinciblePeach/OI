#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e6 + 10;
int n, m, a[MAXN];

void solve() {
    deque<pii> q1, q2;
    for (int i = 1; i <= n; i++) q1.emplace_back(a[i], i);
    int ans;
    while (true) {
        if (q1.size() + q2.size() == 2) {
            ans = 1;
            break;
        }
        int x, id, y;
        y = q1.front().first, q1.pop_front();
        if (q2.empty() || (!q1.empty() && q1.back() > q2.back()))
            x = q1.back().first, id = q1.back().second, q1.pop_back();
        else
            x = q2.back().first, id = q2.back().second, q2.pop_back();
        pii nw = {x - y, id};
        if (q1.empty() || q1.front() > nw) {
            ans = q1.size() + q2.size() + 2;
            int cnt = 0;
            while (true) {
                cnt++;
                if (q1.size() + q2.size() == 1) {
                    if (!(cnt & 1)) ans--;
                    break;
                }
                int x, id;
                if (q2.empty() || (!q1.empty() && q1.back() > q2.back()))
                    x = q1.back().first, id = q1.back().second, q1.pop_back();
                else
                    x = q2.back().first, id = q2.back().second, q2.pop_back();
                nw = {x - nw.first, id};
                if ((q1.empty() || nw < q1.front()) && (q2.empty() || nw < q2.front())) continue;
                if (!(cnt & 1)) ans--;
                break;
            }
            break;
        } else
            q2.emplace_front(nw);
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> m >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    solve();
    for (int i = 1, k, x, y; i < m; i++) {
        cin >> k;
        while (k-- > 0) cin >> x >> y, a[x] = y;
        solve();
    }

    return 0;
}