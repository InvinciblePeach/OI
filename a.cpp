#include <bits/stdc++.h>
#define int long long

using namespace std;
const int MAXN = 1e5 + 10;
int T, n, x, a[MAXN], d[MAXN], sum[MAXN];
int q[MAXN], l, r;

bool check(int k, int val) {
    l = 1, r = 0;
    for (int i = 1; i < k; i++) {
        while (l <= r && a[q[r]] <= a[i])
            r--;
        q[++r] = i;
    }
    for (int i = 1, j = k; j <= n; i++, j++) {
        while (l <= r && a[q[r]] <= a[j])
            r--;
        q[++r] = j;
        while (q[l] < i)
            l++;
        int mx = a[q[l]];

        int tmp = sum[j - 1] - sum[i - 1];
        int bef = 0, aft = 0;
        if (i > 1) {
            bef += abs(a[i - 1] - a[i]);
            aft += abs(a[i - 1] - mx);
        }
        if (j < n) {
            bef += abs(a[j] - a[j + 1]);
            aft += abs(mx - a[j + 1]);
        }
        int res = tmp + (bef - aft);
        if (res >= val) return true;
    }
    return false;
}

void solve() {
    memset(a, 0, (n + 5) << 2);
    memset(d, 0, (n + 5) << 2);
    memset(sum, 0, (n + 5) << 2);
    cin >> n >> x;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 1; i < n; i++) {
        d[i] = abs(a[i] - a[i + 1]);
        sum[i] = sum[i - 1] + d[i];
    }
    if (sum[n - 1] <= x) return cout << 0 << "\n", void();

    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid, sum[n - 1] - x))
            r = mid;
        else
            l = mid + 1;
    }
    cout << l << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T-- > 0)
        solve();

    return 0;
}