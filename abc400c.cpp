#include <bits/stdc++.h>
#define int long long

using namespace std;

int n, ans;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 2; i <= n; i <<= 1) {
        int tmp = sqrtl(n / i);
        ans += tmp / 2 + (tmp & 1);
    }
    assert(n >= ans);
    cout << ans << '\n';

    return 0;
}