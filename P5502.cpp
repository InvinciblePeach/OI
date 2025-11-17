#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e5 + 10;
int n, ans, a[MAXN], q[MAXN], l = 1, r = 0;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        static int st[MAXN];
        int lst = 0, top = 0;
        while (l <= r) {
            int x = q[l++];
            a[x] = gcd(a[x], a[i]);
            ans = max(ans, a[x] * (i - x + 1));
            if (a[x] == lst) continue;
            st[++top] = x;
            lst = a[x];
        }
        ans = max(ans, a[i]);
        memcpy(q, st, (top + 1) << 3);
        l = 1, r = top;
        if (lst ^ a[i]) q[++r] = i;
    }
    cout << ans << '\n';

    return 0;
}