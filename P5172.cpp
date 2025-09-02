#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ld = long double;
using lld = __float128;

const int MAXN = 1e5 + 10;
int T, n, r;

struct Node {
    int x, y;
    Node operator*(const Node &o) const { return {x * o.x, y + x * o.y}; }
};

Node qpow(Node a, int b) {
    auto res = a;
    b--;
    while (b) {
        if (b & 1) res = res * a;
        if (b >>= 1) a = a * a;
    }
    return res;
}

Node solve(lld k, int n, Node U, Node R) {
    if (n < 1) return {1, 0};
    if (k > 1) {
        int tmp = k;
        return solve(k - tmp, n, U, qpow(U, tmp) * R);
    } else {
        int tmp = n * k;
        return solve(1 / k, tmp, R, U) * qpow(R, ceil(ld((n * k - tmp) / k)));
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T-- > 0) {
        cin >> n >> r;
        int k = sqrtf128(r);
        if (k * k == r) {
            cout << ((k & 1) ? -(n & 1) : n) << '\n';
            continue;
        }
        cout << solve(sqrtf128(r), n, {-1, 0}, {1, 1}).y << '\n';
    }

    return 0;
}