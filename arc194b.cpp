#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int n, a[MAXN];
ll ans;

class fenwick {
    int t[MAXN];

    constexpr int lowbit(const int &x) { return x & -x; }

public:
    void add(int x, int val) {
        for (; x <= MAXN; x += lowbit(x))
            t[x] += val;
    }
    int query(int x) {
        int res = 0;
        for (; x; x -= lowbit(x))
            res += t[x];
        return res;
    }
} t;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1, tmp; i <= n; i++) {
        cin >> a[i];
        tmp = t.query(n) - t.query(a[i]);
        t.add(a[i], 1);
        ans += tmp * (2ll * i - tmp - 1) >> 1;
    }
    cout << ans << '\n';

    return 0;
}