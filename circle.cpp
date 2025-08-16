#include <bits/stdc++.h>
#define int unsigned long long

using namespace std;

int n, a[400005];
int ans = ULLONG_MAX;

signed main() {
//    freopen("circle.in", "r", stdin);
//    freopen("circle.out", "w", stdout);

    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        a[n + i] = a[i];
    }

    for (int k = 1; k < n; k ++) {
        int cnt_1 = 0, max_1 = 0;
        int cnt_3 = 0, max_3 = 0;
        for (int i = 1; i <= k; i ++) {
            if (a[i] == 0) { cnt_1 ++; max_3 = max(cnt_3, max_3 + 1); }
            else { cnt_3 ++; max_1 = max(cnt_1, max_1 + 1); }
        }

        int cnt_2 = 0, max_2 = 0;
        int cnt_4 = 0, max_4 = 0;
        for (int i = k + 1; i <= n; i ++) {
            if (a[i] == 1) { cnt_2 ++; max_4 = max(cnt_4, max_4 + 1); }
            else { cnt_4 ++; max_2 = max(cnt_2, max_2 + 1); }
        }
//        cout << k << max_1 + max_2 << max_3 + max_4 << endl;

        ans = min({max_1 + max_2, max_3 + max_4, ans});
    }
    cout << ans << endl;

//    fclose(stdin);
//    fclose(stdout);
    return 0;
}