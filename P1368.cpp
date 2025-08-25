#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 6e5 + 10;
int n, ans;
int s[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i], s[i + n] = s[i];
    int i = 1;
    while (i <= n) {
        int j = i, k = i + 1;
        while (k <= (n << 1) && s[j] <= s[k])
            j = (s[j] == s[k++] ? j + 1 : i);
        while (i <= j)
            i += k - j, ans = i <= n ? i : ans;
    }
    if (!ans) ans = n;
    for (int i = 1; i <= n; i++)
        cout << s[ans - 1 + i] << " \n"[i == n];

    return 0;
}