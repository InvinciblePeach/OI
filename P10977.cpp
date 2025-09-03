#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e5 + 10;
int n, m, a[MAXN], dp[MAXN];
int l = 1, r = 0, q[MAXN];
multiset<int> st;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] > m) {
            cout << "-1\n";
            return 0;
        }
    }
    for (int i = 1, j = 1, sum = 0; i <= n; i++) {
        sum += a[i];
        while (sum > m) {
            sum -= a[j++];
            while (l <= r && q[l] < j) {
                if (l < r) st.erase(st.find(dp[q[l]] + a[q[l + 1]]));
                l++;
            }
        }
        while (l <= r && a[q[r]] <= a[i]) {
            if (l < r) st.erase(st.find(dp[q[r - 1]] + a[q[r]]));
            // cerr << ':' << r << '\n';
            r--;
        }
        q[++r] = i;
        if (l < r) st.emplace(dp[q[r - 1]] + a[q[r]]);
        dp[i] = dp[j - 1] + a[q[l]];
        if (!st.empty()) dp[i] = min(dp[i], *st.begin());
    }
    cout << dp[n] << '\n';

    return 0;
}