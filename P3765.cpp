#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

const int MAXN = 1e5 + 10, K = 15;
typedef long long ll;

int n, m, ans, a[MAXN];
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> t[MAXN];

int solve(int l, int r) {
    static auto calc = [=](const int &x, const int &l, const int &r) -> int { return t[x].order_of_key(r + 1) - t[x].order_of_key(l); };
    int len = r - l + 1;
    for (int i = 1, x; i <= K; i++) {
        x = a[rnd() % len + l];
        if (calc(x, l, r) > (len >> 1)) return x;
    }
    return -1;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) t[cin >> a[i], a[i]].insert(i);

    while (m --> 0) {
        static int l, r, k, s, pos[MAXN];
        cin >> l >> r >> s >> k;
        for (int i = 1; i <= k; i++) cin >> pos[i];
        int ans = solve(l, r);
        if (!~ans) ans = s;
        cout << ans << '\n';

        for (int i = 1; i <= k; i++) {
            t[a[pos[i]]].erase(pos[i]);
            t[a[pos[i]] = ans].insert(pos[i]);
        }
    }
    cout << solve(1, n) << '\n';
}