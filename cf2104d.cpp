#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 5e6 + 10;
int t, n, a[MAXN], sum[MAXN];
bitset<MAXN> p;
vector<int> prime;

void init() {
    for (int i = 2; i < MAXN; i++) {
        if (!p[i]) prime.emplace_back(i);

        for (auto j : prime) {
            if (i * j >= MAXN) break;
            p[i * j] = 1;
            if (i % j == 0) break;
        }
    }
    for (int i = 0; i < prime.size(); i++)
        sum[i + 1] = sum[i] + prime[i];
}

void solve() {
    cin >> n;
    // if (n == 0) return cout << 0 << '\n', void();
    // if (n == 1) return cout << -1 << '\n', void();
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a + 1, a + 1 + n, greater<>());
    static int ans, s;
    for (ans = 1, s = 0; ans <= n; ans++)
        if ((s += a[ans]) < sum[ans]) break;
    cout << n - (ans - 1) << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    init();
    cerr << '=';
    cin >> t;
    while (t --> 0) {
        solve();
    }

    return 0;
}