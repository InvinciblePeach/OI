#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e4 + 10;
int T, n, k, mid, cnt;
vector<int> g[MAXN];
int ans[MAXN];

void dfs(int u, int fa, int len, int dep) {
    if (u >= mid) len++;
    if (len >= (dep >> 1) + 1) cnt++;
    for (auto v : g[u]) {
        if (v != fa) continue;
        dfs(v, u, len, dep + 1);
    }
}

bool check() {
    cnt = 0;
    dfs(1, 0, 0, 0);
    return cnt >= k;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for (int i = 1; i <= n; i++) g[i].clear();
        for (int i = 1, u, v; i < n; i++) {
            cin >> u >> v;
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        for (k = 1; k <= n; k++) {
            int l = 1, r = n, res;
            while (l <= r) {
                mid = (l + r) >> 1;
                if (check()) {
                    res = mid;
                    l = mid + 1;
                } else
                    r = mid - 1;
            }
            ans[k] = res;
        }
        for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];
    }
    return 0;
}
