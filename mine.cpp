#include <bits/stdc++.h>
#define int long long
#define make_pair mp

using namespace std;

typedef long double ld;
const int MAXN = 1e5 + 10;
int n;
pair<int, int> pts[MAXN];
map<pair<int, int>, int> cnt[4];

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

signed main() {
    freopen("mine.in", "r", stdin);
    freopen("mine.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        int tmp = gcd(abs(x), abs(y));
        if (x > 0 && y > 0) cnt[0][{x / tmp, y / tmp}]++;
        if (x < 0 && y > 0) cnt[1][{-x / tmp, y / tmp}]++;
        if (x < 0 && y < 0) cnt[2][{-x / tmp, -y / tmp}]++;
        if (x > 0 && y < 0) cnt[3][{x / tmp, -y / tmp}]++;
        if (x > 0 && y == 0) cnt[0][{0, 0}]++;
        if (x == 0 && y > 0) cnt[1][{0, 0}]++;
        if (x < 0 && y == 0) cnt[2][{0, 0}]++;
        if (x == 0 && y < 0) cnt[3][{0, 0}]++;
        pts[i] = {x, y};
    }

    for (int i = 1, x, y; i <= n; i++) {
        x = pts[i].first, y = pts[i].second;
        int tmp = gcd(abs(x), abs(y));
        if (x > 0 && y > 0)
            cout << cnt[0][{x / tmp, y / tmp}] << '\n', cnt[0][{x / tmp, y / tmp}] = 0;
        if (x < 0 && y > 0)
            cout << cnt[1][{-x / tmp, y / tmp}] << '\n', cnt[1][{-x / tmp, y / tmp}] = 0;
        if (x < 0 && y < 0)
            cout << cnt[2][{-x / tmp, -y / tmp}] << '\n', cnt[2][{-x / tmp, -y / tmp}] = 0;
        if (x > 0 && y < 0)
            cout << cnt[3][{x / tmp, -y / tmp}] << '\n', cnt[3][{x / tmp, -y / tmp}] = 0;
        if (x > 0 && y == 0)
            cout << cnt[0][{0, 0}] << '\n', cnt[0][{0, 0}] = 0;
        if (x == 0 && y > 0)
            cout << cnt[1][{0, 0}] << '\n', cnt[1][{0, 0}] = 0;
        if (x < 0 && y == 0)
            cout << cnt[2][{0, 0}] << '\n', cnt[2][{0, 0}] = 0;
        if (x == 0 && y < 0)
            cout << cnt[3][{0, 0}] << '\n', cnt[3][{0, 0}] = 0;
    }
}