#include <bits/stdc++.h>

using namespace std;

int n, a[3000005], ans[3000005];
stack<int> s; // NOLINT

int main() {
    cin >> n;
    for (int i = 1; i <= n; i ++) { cin >> a[i]; }

    for (int i = n; i >= 1; i --) {
        while (!s.empty() && a[s.top()] <= a[i]) { s.pop(); }
        if (s.empty()) {
            ans[i] = 0;
        } else { ans[i] = s.top(); }
        s.emplace(i);
    }
    for (int i = 1; i <= n; i ++) { cout << ans[i] << ' '; }
    return 0;
}