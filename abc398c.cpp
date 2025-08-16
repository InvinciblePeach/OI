#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 3e5 + 10;
int n, ans = -1;

struct Node {
    int w, id;

    bool operator<(const Node &o) { return w < o.w; }
} a[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].w, a[i].id = i;
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; i++)
        if (a[i - 1].w != a[i].w && a[i + 1].w != a[i].w) ans = a[i].id;
    cout << ans << '\n';

    return 0;
}