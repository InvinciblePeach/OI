#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 3e5 + 10;
int n, l, a[MAXN], cnt[MAXN], ans;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> l;
    a[1] = 0;
    cnt[0] = 1;
    for (int i = 2, d; i <= n; i++) {
        cin >> d;
        cnt[a[i] = (d + a[i - 1]) % l]++;
    }
    if (l % 3) {
        cout << 0;
        return 0;
    }
    for (int i = 0; i < l / 3; i++) {
        ans += cnt[i] * cnt[i + l / 3] * cnt[i + 2 * l / 3];
    }
    cout << ans << '\n';

    return 0;
}