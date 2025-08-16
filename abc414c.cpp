#include <bits/stdc++.h>
#define int long long

using namespace std;
int a, n, ans, D;

bool check(int x, int a) {
    vector<int> tmp;
    while (x > 0) {
        tmp.push_back(x % a);
        x /= a;
    }
    for (int i = 0, j = tmp.size() - 1; i < j; i++, j--)
        if (tmp[i] != tmp[j]) return false;
    return true;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> a >> n;

    int ans = 0;
    string s;
    int D = to_string(n).size();

    for (int d = 1; d <= D; d++) {
        int len = (d + 1) >> 1;
        int st = (len == 1 ? 1 : (int)pow(10, len - 1));
        int ed = (int)pow(10, len) - 1;

        for (int j = st; j <= ed; j++) {
            s = to_string(j);
            for (int i = d % 2 ? len - 2 : len - 1; i >= 0; i--) {
                s.push_back(s[i]);
            }

            int p = stoll(s);
            if (p > n) break;
            if (check(p, a)) ans += p;
        }
    }

    cout << ans << '\n';
    return 0;
}
