#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 3e5 + 10;
int n, m, ans, cnt[MAXN];
vector<int> pos[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> cnt[i];
        for (int j = 1, t; j <= cnt[i]; j++)
            cin >> t, pos[t].emplace_back(i);
    }

    for (int i = 1, b; i <= n; i++) {
        cin >> b;
        for (auto j : pos[b])
            if (--cnt[j] == 0) ans++;
        cout << ans << '\n';
    }

    return 0;
}