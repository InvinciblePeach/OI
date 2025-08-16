#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
const int MAXN = 1e5;
const ll MAXV = 1e9;
int n, m;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    n = MAXN, m = MAXN;
    cout << n << ' ' << m << '\n';
    for (int i = 1; i <= n;) {
        ll tmp = 1ll << (rnd() % 30);
        for (int cnt = 0; i <= n && cnt <= 1000; cnt++, i++) cout << tmp << " \n"[i == n];
    }
    for (int i = 1; i <= m; i++) {
        int l = rnd() % n + 1, r = rnd() % n + 1;
        if (l > r) swap(l, r);
        cout << "2" << ' ' << l << ' ' << r << ' ' << (rnd() % MAXV) << '\n';
    }

    return 0;
}