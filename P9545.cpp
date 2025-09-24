#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 3010;
int n, m, siz, sum, deg[MAXN], p[MAXN];
bitset<MAXN> vis;
string s;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        s = ' ' + s;
        for (int j = 1; j <= n; j++)
            if (s[j] == '1') deg[i]++, deg[j]--;
    }
    for (int i = 1; i <= n; i++) p[i] = i;
    sort(p + 1, p + 1 + n, [=](int a, int b) { return deg[a] < deg[b]; });
    while (m-- > 0) {
        static int t, k;
        cin >> t >> k;
        vis.reset();
        siz = sum = 0;
        while (k-- > 0) {
            int x;
            cin >> x;
            vis[x] = 1;
            sum += deg[x], siz++;
        }
        int ans = (sum + siz * (n - siz)) >> 1;
        for (int i = 1; i <= n; i++) {
            if (vis[p[i]] || p[i] == t) continue;
            sum += deg[p[i]], siz++;
            ans = min(ans, (sum + siz * (n - siz)) >> 1);
        }
        cout << ans << '\n';
    }

    return 0;
}