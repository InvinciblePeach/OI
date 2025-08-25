#include <bits/stdc++.h>

using namespace std;

int n;
set<pair<int, int>> st;

signed main() {
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int x = 1; x * x <= i; x++) {
            if (i % x) continue;
            int tmp = i ^ x;
            if (tmp && tmp <= n && __gcd(tmp, i) == x) st.emplace(min(tmp, i), max(tmp, i));
            tmp = i ^ (i / x);
            if (tmp && tmp <= n && __gcd(tmp, i) == (i / x)) st.emplace(min(tmp, i), max(tmp, i));
        }
    }
    // for (auto [a, b] : st) cerr << a << ' ' << b << '\n';
    cout << st.size() << '\n';
    return 0;
}