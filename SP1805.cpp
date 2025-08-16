#include <bits/stdc++.h>
#define int unsigned long long

using namespace std;

int n, ans, a[100005];
stack<pair<int, int>> s; // NOLINT

signed main() {
    while (cin >> n && n) {
        memset(a, 0, sizeof(a));
        while (!s.empty()) { s.pop(); }
        ans = 0;
        for (int i = 1; i <= n; i ++) {
            cin >> a[i];
        }
        for (int i = 1; i <= n + 1; i ++) {
            if (s.empty() || a[i] >= s.top().first) { s.emplace(make_pair(a[i], 1)); }
            else {
                int width = 0;
                while (!s.empty() && a[i] < s.top().first) {
                    int v = s.top().first, j = s.top().second;
                    width += j;
                    ans = max(ans, width * v);
                    s.pop();
                }
                s.emplace(make_pair(a[i], width + 1));
            }
        }
        cout << ans << endl;
    }
    return 0;
}