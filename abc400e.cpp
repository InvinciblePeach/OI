#include <bits/stdc++.h>
#define int long long

using namespace std;

int q, n;

void solve() {
    cin >> n;
    int tmp = sqrt(n);
    int a = tmp;
    int cnt = 0;
    for (int i = 2; i * i <= tmp; i++) {
        while (tmp % i == 0)
            tmp /= i, cnt++;
    }
    if (tmp > 1) cnt++;
    cout << (cnt > 1 ? a * a : (a - 1) * (a - 1)) << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> q;
    while (q --> 0) solve();

    return 0;
}