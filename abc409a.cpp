#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 110;
int n, a[MAXN], cnt, ans;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cnt = 0;
        for (int j = 1; j <= n; j++)
            if (a[j] >= i) cnt++;
        if (cnt >= i) ans = i;
        else break;
    }
    cout << ans << '\n';

    return 0;
}