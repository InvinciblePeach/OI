#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int T, n, mx[MAXN], mn[MAXN], l[MAXN], r[MAXN], d[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> d[i];
        for (int i = 1; i <= n; i++) cin >> l[i] >> r[i];

        bool flag = true;
        for (int i = 1; i <= n; i++) {
            if (d[i] == 0) mx[i] = mx[i - 1], mn[i] = mn[i - 1];
            else if (d[i] == 1) mx[i] = mx[i - 1] + 1, mn[i] = mn[i - 1] + 1;
            else if (d[i] == -1) mx[i] = mx[i - 1] + 1, mn[i] = mn[i - 1];
            if (mn[i] < l[i]) {
                if (mx[i] >= l[i]) mn[i] = l[i];
                else {
                    flag = false;
                    break;
                }
            }
            if (mx[i] > r[i]) {
                if (mn[i] <= r[i]) mx[i] = r[i];
                else {
                    flag = false;
                    break;
                }
            }
        }
        if (!flag) {
            cout << "-1\n";
            continue;
        }
        int h = mn[n];
        for (int i = n; i; i--) {
            if (d[i] == -1) {
                if (mn[i - 1] < h) d[i] = 1;
                else d[i] = 0;
            }
            h -= d[i];
        }
        for (int i = 1; i <= n; i++) cout << d[i] << " \n"[i == n];
    }

    return 0;
}