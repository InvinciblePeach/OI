#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int T, n, k, a[MAXN];
int pre[MAXN], suf[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T-- > 0) {
        cin >> n >> k;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        for (int i = 1; i <= n; i++)
            pre[i] = pre[i - 1] + (a[i] <= k);
        suf[n + 1] = 0;
        for (int i = n; i; i--)
            suf[i] = suf[i + 1] + (a[i] <= k);
        int l = -1, r = -1, ans = 0;
        for (int i = 1; i <= n; i++)
            if ((pre[i] << 1) >= i) ans |= (~l) && pre[i] > 1, l = (!ans ? i : l);

        for (int i = n; i >= 1; i--)
            if ((suf[i] << 1) >= (n - i + 1)) ans |= (~r) && suf[i] > 1, r = (!ans ? i : r);

        ans |= (~l) && (~r) && (l < r);

        cout << (ans ? "YES\n" : "NO\n");
    }

    return 0;
}