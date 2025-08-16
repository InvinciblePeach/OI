#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 3e5 + 10;
int n, p[MAXN], ans;
int sum[MAXN], l1[MAXN], l2[MAXN], r1[MAXN], r2[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> p[i];


    for (int i = 2; i <= n; i++) {
        if (p[i - 1] < p[i])
            l1[i] = l1[i - 1] + 1;
        if (p[i - 1] > p[i])
            l2[i] = l2[i - 1] + 1;
    }

    for (int i = n - 1; i >= 1; i--) {
        if (p[i] < p[i + 1])
            r1[i] = r1[i + 1] + 1;
        if (p[i] > p[i + 1])
            r2[i] = r2[i + 1] + 1;
    }

    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i - 1] + r1[i];
    }

    for (int i = 2; i <= n - 2; ++i) {
        if (l1[i] == 0 || r2[i] == 0) continue;

        int r = min(n - 1, i + r2[i]);
        int rsum = sum[r] - sum[i];
        ans += l1[i] * rsum;
    }
    cout << ans << '\n';

    return 0;
}