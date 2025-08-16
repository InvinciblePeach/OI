#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 5e5 + 10;
int n, m, cnt;
bitset<MAXN> a;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    while (m --> 0) {
        static int p;
        cin >> p;
        if (a[p] == 1) {
            if (a[p - 1] == 0 && a[p + 1] == 0) cnt--;
            if (a[p - 1] == 1 && a[p + 1] == 1) cnt++;
        } else {
            if (a[p - 1] == 1 && a[p + 1] == 1) cnt--;
            if (a[p - 1] == 0 && a[p + 1] == 0) cnt++;
        }
        a[p] = a[p] ^ 1;
        cout << cnt << '\n';
    }

    return 0;
}