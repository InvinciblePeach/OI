#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int n, ans = 1;
string s;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> s;
    n = s.size(), s = ' ' + s;
    for (int i = 2; i <= n; i++) {
        ans += (s[i - 1] - s[i] + 10) % 10 + 1;
    }
    ans += s[n] - '0';
    cout << ans << '\n';

    return 0;
}