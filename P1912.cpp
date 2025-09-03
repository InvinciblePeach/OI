#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using lll = __int128;
using pii = pair<int, int>;

const int MAXN = 1e5 + 10;
int T, n, m, p, sum[MAXN], k[MAXN], pre[MAXN];
lll dp[MAXN];
int q[MAXN], l, r;
string s[MAXN];

lll qpow(lll a, int b) {
    lll res = 1;
    while (b) {
        if (b & 1) res *= a;
        if (b >>= 1) a *= a;
    }
    return res;
}

lll calc(int i, int j) { return dp[j] + qpow(abs(sum[i] - sum[j] - m), p); }

int find(int x, int y) {
    int l = x, r = n + 1, res = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (calc(mid, x) >= calc(mid, y))
            res = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T-- > 0) {
        cin >> n >> m >> p;
        m++;
        for (int i = 1; i <= n; i++) cin >> s[i], sum[i] = sum[i - 1] + s[i].size() + 1;
        q[l = r = 1] = 0;
        for (int i = 1; i <= n; i++) {
            while (l < r && k[l] <= i) l++;
            dp[i] = calc(i, q[l]), pre[i] = q[l];
            while (l < r && k[r - 1] >= find(q[r], i)) r--;
            k[r] = find(q[r], i);
            q[++r] = i;
        }
        if (dp[n] > 1e18) {
            cout << "Too hard to arrange\n";
        } else {
            cout << (ll)dp[n] << '\n';
            q[r = 0] = n;
            for (int i = n; i; q[++r] = i = pre[i]) {
            }
            for (; r; r--) {
                for (int i = q[r] + 1; i <= q[r - 1]; i++) cout << s[i] << " \n"[i == q[r - 1]];
            }
        }
        cout << "--------------------\n";
    }
    return 0;
}