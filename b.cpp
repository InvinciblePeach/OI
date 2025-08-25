#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 110;
int n, a[MAXN];
pii b[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        b[i] = {a[i], i};
    sort(b + 1, b + 1 + n);
    int mx = 1, cur = 1;
    for (int i = 2; i <= n; i++) {
        if (b[i].second > b[i - 1].second)
            cur++, mx = max(mx, cur);
        else
            cur = 1;
    }
    cout << n - mx << '\n';
    return 0;
}
