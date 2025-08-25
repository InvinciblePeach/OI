#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e5, mod = 1e9;
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cout << 1 << '\n';
    cout << MAXN << '\n';
    for (int i = 1; i <= MAXN; i++) cout << (i & 1 ? 114514 : 1919810) << " \n"[i == MAXN];
    cout << MAXN << '\n';
    for (int i = 1; i <= MAXN; i++) {
        cout << 2 << ' ' << 1 << ' ' << MAXN << ' ' << 1919810 << '\n';
    }

    return 0;
}