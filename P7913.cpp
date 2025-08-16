#include <bits/stdc++.h>

using namespace std;

int n, x, y, ans = INT_MIN;
int cnt_a[500005], cnt_b[500005];
pair<int, int> a[500005], b[500005]; // NOLINT
priority_queue<pair<int/*in*/, int/*out*/>, vector<pair<int, int>>, greater<>> plane; // NOLINT
priority_queue<int, vector<int>, greater<>> empty_; // NOLINT

int main() {
    cin >> n >> x >> y;
    for (int i = 1; i <= x; i ++) { cin >> a[i].first >> a[i].second; }
    for (int i = 1; i <= y; i ++) { cin >> b[i].first >> b[i].second; }

    sort(a + 1, a + 1 + x);
    sort(b + 1, b + 1 + y);

    for (int i = 1; i <= n; i ++) { empty_.emplace(i); }
    for (int i = 1; i <= x; i ++) {
        while (!plane.empty() && plane.top().first <= a[i].first) {
            empty_.emplace(plane.top().second);
            plane.pop();
        }
        if (empty_.empty()) { continue; }
        int tmp = empty_.top();
        empty_.pop();
        cnt_a[tmp] ++;
        plane.emplace(make_pair(a[i].second, tmp));
    }

    while (!plane.empty()) { plane.pop(); }
    while (!empty_.empty()) { empty_.pop(); }

    for (int i = 1; i <= n; i ++) { empty_.emplace(i); }
    for (int i = 1; i <= y; i ++) {
        while (!plane.empty() && plane.top().first <= b[i].first) {
            empty_.emplace(plane.top().second);
            plane.pop();
        }
        if (empty_.empty()) { continue; }
        int tmp = empty_.top();
        empty_.pop();
        cnt_b[tmp] ++;
        plane.emplace(make_pair(b[i].second, tmp));
    }

    for (int i = 1; i <= n; i ++) { cnt_a[i] += cnt_a[i - 1]; }
    for (int i = 1; i <= n; i ++) { cnt_b[i] += cnt_b[i - 1]; }

    for (int i = 0; i <= n; i ++) { ans = max(ans, cnt_a[i] + cnt_b[n - i]); }
    cout << ans << endl;
    return 0;
}