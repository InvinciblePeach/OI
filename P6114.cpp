#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 5e6 + 10;
int n, ans;
string s;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> s;
    n = s.size(), s = ' ' + s;
    int i = 1;
    while (i <= n) {
        int j = i, k = i + 1;
        while (k <= n && s[j] <= s[k]) j = (s[j] == s[k++] ? j + 1 : i);
        while (i <= j) i += k - j, ans ^= i - 1;
    }
    cout << ans << '\n';

    return 0;
}