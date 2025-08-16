#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 1e6 + 10, mod = 1e9 + 7;
int n, a[MAXN], sum[MAXN], q[MAXN], dp[MAXN], pre[MAXN], lst[4];
bitset<MAXN> p;
char s[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        a[i] = sum[i] = s[i] - 'A' + 1;
    }
    for (int i = 1; i <= n; i++) sum[i] ^= sum[i - 1];

    dp[1] = lst[a[1]] = 1;
    bool flag = true;
    for (int i = 2; i <= n; i++) {
        flag &= (a[i] == a[i - 1]);
        p[i] = flag, pre[i] = lst[sum[i]];
        if (!flag && sum[i]) dp[i]++;

        for (int j = 1; j <= 3; j++) {
            int nw = lst[sum[i] ^ j];
            (dp[i] += dp[nw]) %= mod;

            if (!p[i] && p[nw]) {
                if (q[nw]) {
                    (dp[i] += q[nw]) %= mod;
                    continue;
                }

                int tmp = pre[nw];
                while (tmp) {
                    (q[nw] += dp[tmp]) %= mod;
                    (dp[i] += dp[tmp]) %= mod;
                    tmp = pre[tmp];
                }
            }
        }
        lst[sum[i]] = i;
    }
    cout << dp[n] << '\n';
    return 0;
}