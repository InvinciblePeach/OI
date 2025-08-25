#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef __int128 iit;

const int MAXN = 1e5 + 10, mod = 998244353;
int T, n, a, b, c;

struct Node {
    int x, y, sumx, sumy, sumy2, sumxy;
    Node() : x(0), y(0), sumx(0), sumy(0), sumy2(0), sumxy(0) {}
    Node operator*(const Node &o) {
        Node res;
        res.x = (x + o.x) % mod;
        res.y = (y + o.y) % mod;
        res.sumx = (sumx + o.sumx + x * o.x) % mod;
        res.sumy = (sumy + o.sumy + y * o.x) % mod;
        res.sumy2 =
            (sumy2 + o.sumy2 + 2 * y * o.sumy + o.x * y % mod * y) % mod;
        res.sumxy =
            (sumxy + o.sumxy + y * o.sumx + x * o.sumy + o.x * x % mod * y) %
            mod;
        return res;
    }
};

Node qpow(Node a, int b) {
    Node res;
    while (b) {
        if (b & 1) res = res * a;
        a = a * a, b >>= 1;
    }
    return res;
}

Node spgcd(int p, int q, int r, int n, Node U, Node R) {
    if (!n) return Node();
    if (r >= q) return qpow(U, r / q) * spgcd(p, q, r % q, n, U, R);
    if (p >= q) return spgcd(p % q, q, r, n, U, qpow(U, p / q) * R);
    int m = (p * n + r) / q;
    if (!m) return qpow(R, n);
    return qpow(R, (q - r - 1) / p) * U *
           spgcd(q, p, (q - r - 1) % p, m - 1, R, U) *
           qpow(R, n - (q * m - r - 1) / p);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    Node U, R;
    U.y = 1, R.x = 1, R.sumx = 1;
    while (T --> 0) {
        cin >> n >> a >> b >> c;
        Node ans = spgcd(a, c, b, n, U, R);
        (ans.sumy += b / c) %= mod;
        (ans.sumy2 += (b / c) * (b / c)) %= mod;
        cout << (ans.sumy + mod) % mod << ' ' << (ans.sumy2 + mod) % mod << ' '
             << (ans.sumxy + mod) % mod << '\n';
    }

    return 0;
}