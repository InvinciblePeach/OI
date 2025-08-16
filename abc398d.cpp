#include <bits/stdc++.h>
#define mp(a, b)  make_pair(a, b)

using namespace std;
typedef long long ll;

const int MAXN = 55;
int n, r, c, x, y;
string s;
map<pair<int, int>, bool> p;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> r >> c;
    cin >> s;
    p[mp(0, 0)] = 1;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'N') x++, r++;
        if (s[i] == 'W') y++, c++;
        if (s[i] == 'S') x--, r--;
        if (s[i] == 'E') y--, c--;
        // cerr << x << ',' << y << '\n';
        // cerr << r << ',' << c << '\n';
        p[mp(x, y)] = 1;
        if (p[mp(r, c)]) cout << '1';
        else cout << '0';
    }

    return 0;
}