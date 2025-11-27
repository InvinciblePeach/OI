#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 5e5 + 10, MAXM = 110;
int n, m, ans;
struct Node {
    int x, y;

    bool operator<(const Node &o) const { return x < o.x; }
} t[MAXM];

void solve() {
    for (int i = 1; i <= m; i++) {
        int l = 0, r = n + 1;
        for (int j = i + 1; j <= m; j++) {
            if (r - l - 1 < t[j].x - t[i].x - 1) break;
            ans = max(ans, t[j].x - t[i].x - 1);
            if (t[j].y <= t[i].y) l = max(l, t[j].y);
            if (t[j].y >= t[i].y) r = min(r, t[j].y);
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> t[i].x >> t[i].y;
    t[++m] = {0, 0};
    t[++m] = {0, n + 1};
    t[++m] = {n + 1, 0};
    t[++m] = {n + 1, n + 1};
    sort(t + 1, t + 1 + m);
    solve();
    for (int i = 1; i <= m; i++) swap(t[i].x, t[i].y);
    sort(t + 1, t + 1 + m);
    solve();
    cout << ans << '\n';

    return 0;
}