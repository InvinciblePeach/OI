#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int T, n, a[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        sort(a + 2, a + n);
        // for (int i =1; i <= n; i++) cerr << a[i] << " \n"[i == n];
        int nw = a[1], id = 1, cnt = 1;
        if (a[1] >= a[n]) {
            cout << "2\n";
            continue;
        }
        while (nw < a[n]) {
            if ((nw << 1) >= a[n])  { cnt++; break; }
            int tmp = upper_bound(a + 2, a + n, (nw << 1)) - a - 1;
            if (tmp == id) {
                cnt = -1;
                break;
            }
            nw = a[id = tmp], cnt++;
        }
        cout << cnt << '\n';
    }

    return 0;
}