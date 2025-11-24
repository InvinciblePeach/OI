#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e5 + 10;
int n, x[MAXN], a[MAXN], b[MAXN];

bool check(int val) {
    int l = 0, r = 1e9;
    for (int i = 1; i <= n; i++) {
        if (a[i] == b[i]) {
            if (val * b[i] > x[i]) return false;
        } else if (a[i] > b[i]) {
            if (val * b[i] > x[i]) return false;
            r = min(r, (x[i] - val * b[i]) / (a[i] - b[i]));
        } else
            l = max(l, (val * b[i] - x[i] + b[i] - a[i] - 1) / (b[i] - a[i]));
    }
    if (l > r || r < 0 || l > val) return false;
    return true;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> x[i];
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    int l = 0, r = 1e9, res = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid))
            res = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    cout << res << '\n';

    return 0;
}