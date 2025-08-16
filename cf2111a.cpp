#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int t, k, cnt;
priority_queue<int, vector<int>, greater<>> q;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> t;
    while (t --> 0) {
        cin >> k;
        while (!q.empty()) q.pop();
        cnt = 0;
        q.emplace(0), q.emplace(0), q.emplace(0);
        while (1) {
            int x = q.top(); q.pop();
            if (x == k) break;
            int y = q.top();
            x = min(k, y << 1 | 1);
            q.emplace(x);
            cnt++;
        }
        cout << cnt << '\n';
    }

    return 0;
}