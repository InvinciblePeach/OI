#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e6 + 10;
int n, k, ans, cnt[MAXN], top[MAXN];
ll p[MAXN];
vector<pii> pos[MAXN];
vector<int> r[MAXN], u[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        r[i].resize(k + 1);
        for (int j = 1; j <= k; j++) cin >> r[i][j], pos[j].emplace_back(r[i][j], i);
    }
    for (int i = 1; i <= k; i++) sort(pos[i].begin(), pos[i].end());
    for (int i = 1; i <= n; i++) {
        u[i].resize(k + 1);
        for (int j = 1; j <= k; j++) cin >> u[i][j];
    }
    int tmp = -1;
    while (tmp ^ ans) {
        tmp = ans;
        for (int i = 1; i <= k; i++) {
            while (top[i] < n && pos[i][top[i]].first <= p[i]) {
                if (++cnt[pos[i][top[i]].second] == k) {
                    ans++;
                    for (int j = 1; j <= k; j++) p[j] += u[pos[i][top[i]].second][j];
                }
                top[i]++;
            }
        }
    }
    cout << ans << '\n';

    return 0;
}