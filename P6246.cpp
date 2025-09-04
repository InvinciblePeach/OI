#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 5e5 + 10;
int n, m, a[MAXN], k[MAXN], cnt[MAXN];
ll sum[MAXN], dp[MAXN];
int q[MAXN], l, r;

ll calc(int l, int r) {
    ll mid = (l + r + 1) >> 1;
    return sum[l] + sum[r] - 2 * sum[mid] + ll(2 * mid - l - r) * a[mid];
}

int find(int x, int y) {
    int l = x + 1, r = n, res = n + 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (dp[x] + calc(x, mid) >= dp[y] + calc(y, mid))
            res = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    return res;
}

bool check(int val) {
    q[l = r = 1] = 0;
    k[1] = n;
    for (int i = 1; i <= n; i++) {
        while (l < r && k[l] <= i) l++;
        dp[i] = dp[q[l]] + calc(q[l], i) + val, cnt[i] = cnt[q[l]] + 1;
        while (l < r && k[r - 1] >= find(q[r], i)) r--;
        k[r] = find(q[r], i);
        q[++r] = i;
    }
    return cnt[n] < m;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i], sum[i] = sum[i - 1] + a[i];
    int l = 0, r = 1e9, res = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1;
        else
            res = mid, l = mid + 1;
    }
    check(res);
    cout << dp[n] - res * m << '\n';

    return 0;
}