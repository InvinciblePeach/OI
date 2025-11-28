#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using lll = __int128_t;

const int MAXN = 1e5 + 10;
int n;

struct equ {
    int b, mod;
} t[MAXN];

int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int res = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return res;
}

int excrt() {
    int M = 1, res = 0, A, x, y, tmp;
    for (int i = 1; i <= n; i++) {
        A = t[i].b - res;
        tmp = exgcd(M, t[i].mod, x, y);
        if (A % tmp) return -1;
        res += lll(x) * A / tmp * M % (M / tmp * t[i].mod);
        M *= t[i].mod / tmp;
        res %= M;
    }
    return (res + M) % M;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> t[i].mod >> t[i].b;
    cout << excrt() << '\n';

    return 0;
}