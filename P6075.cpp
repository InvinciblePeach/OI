#include <bits/stdc++.h>
#define int long long
#define rep(x, y, z) for (int x = (y); x <= z; x++)
#define per(x, y, z) for (int x = (y); x >= z; x--)

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 1e5 + 10, mod = 1e9 + 7;
int n, k;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        (a *= a) %= mod, b >>= 1;
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> k;
    cout << qpow(2, n * k % (mod - 1)) << '\n';

    return 0;
}