#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int n, ans;
string s, t;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> s >> t;
    for (int i = 0; i < n; i++) ans += s[i] != t[i];
    cout << ans << '\n';

    return 0;
}