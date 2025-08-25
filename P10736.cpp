#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 2.5e5 + 10;
int n, a[MAXN], ans;
priority_queue<int, vector<int>, greater<>> q;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    q.emplace(0);
    for (int i = 1; i <= n; i++) cin >> a[i], a[i] += a[i - 1];
    for (int i = 1; i <= n; i++) {
        if (!q.empty() && q.top() < a[i]) ans += a[i] - q.top(), q.pop(), q.emplace(a[i]);
        q.emplace(a[i]);
    }
    cout << ans << '\n';

    return 0;
}