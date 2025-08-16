#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll n, cnt, ans = INT_MAX;
ll a[500005], b[500005];

int main() {
    cin >> n;
    for (ll i = 1; i <= n; i ++) { cin >> a[i]; }
    for (ll i = 1; i <= n; i ++) { cin >> b[i]; }

    for (ll i = 1; i <= n; i ++) {
        if (a[i] != b[i]) { cnt ++; }
    }

    ans = min(cnt, ans);
    cnt = 1;

    for (ll i = 1, j = n; i <= n && j >= 1; i ++, j --) {
        if (a[i] == b[j]) { continue; }
        else { cnt ++; }
    }

    ans = min(cnt, ans);

    cout << ans << endl;
    return 0;
}