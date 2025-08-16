#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int h, w, k, mxx, mxy, mnx, mny;
int dx[]{0, 0, 1, -1, 1, -1, 1, -1};
int dy[]{1, -1, -1, 1, 1, -1, 0, 0};
map<pii, bool> vis;
set<pii> st;

void dfs(int x, int y) {
    vis[{x, y}] = 1;
    mxx = max(mxx, x), mxy = max(mxy, y), mnx = min(mnx, x), mny = min(mny, y);
    for (int i = 0; i < 8; i++) {
        if (x + dx[i] > h || x + dx[i] < 1 || y + dy[i] > w || y + dy[i] < 1) continue;
        if (vis[{x + dx[i], y + dy[i]}]) continue;
        if (st.find({x + dx[i], y + dy[i]}) != st.end()) dfs(x + dx[i], y + dy[i]);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> h >> w >> k;
    for (int i = 1, x, y; i <= k; i++) {
        cin >> x >> y;
        st.emplace(x, y);
    }
    for (auto [x, y] : st) {
        if (vis[{x, y}]) continue;
        dfs(mxx = mnx = x, mxy = mny = y);
        if ((mxx == h && mxy == w) || (mnx == 1 && mny == 1) || (mnx == 1 && mxx == h) || (mny == 1 && mxy == w)) {
            return cout << "No\n", 0;
        }
    }
    cout << "Yes\n";

    return 0;
}