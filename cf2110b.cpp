#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int T, n, sum[MAXN];
string s;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        cin >> s;
        n = s.size();
        s = ' ' + s;
        int flag = -1;
        bool res = false;
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + (s[i] == '(' ? 1 : -1);
            if (!(~flag) && !sum[i]) flag = i;
            if (~flag && (flag ^ i) && s[i] == ')') {
                res = true;
                break;
            }
        }
        cout << (res ? "YES\n" : "NO\n");
    }

    return 0;
}