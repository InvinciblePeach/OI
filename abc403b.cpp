#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 15;
int n;
string t, s;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> t >> s;
    n = t.size();
    for (int i = 0; i < n; i++) {
        for (int j = i; j - i < s.size(); j++) {
            if (t[j] != s[j - i] && t[j] != '?') {
                break;
            }
            if (j - i == s.size() - 1) {
                return cout << "Yes\n", 0;
            }
        }
    }
    cout << "No\n";

    return 0;
}