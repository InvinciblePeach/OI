#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10, mod = 1e9 + 7;
int n, c, x[MAXN], y[MAXN], frac[MAXN], dp[MAXN];

struct Point
{
    int x, y;

    bool operator<(const Point &o) const { return x != o.x ? x < o.x : y < o.y; }
} p[MAXN];


int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}

int inv(int x) { return qpow(x, mod - 2); }

int C(int a, int b) { return frac[a] * inv(frac[b]) % mod * inv(frac[a - b]) % mod; }

int g(int x, int y, int a, int b) { 
    if (b < x + 1) return C(a - x + b - y, a - x);
    return (C(a - x + b - y, a - x) - C(a - x + b - y, b - 1 - x) + mod) % mod;
}

signed main() {
    freopen("walk.in", "r", stdin);
    freopen("walk.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> c;
    frac[0] = 1;
    for (int i = 1; i <= (n << 1); i++)
        frac[i] = frac[i - 1] * i % mod;
    for (int i = 1; i <= c; i++)
        cin >> p[i].x >> p[i].y;
    sort(p + 1, p + 1 + c);
    if (x[c] != n && y[c] != n) p[++c] = {n, n};
    dp[0] = 1;
    for (int i = 1; i <= c; i++) {
        dp[i] = g(0, 0, p[i].x, p[i].y);
        for (int j = 1; j < i; j++)
            if (p[j].y <= p[i].y) (dp[i] += mod - (dp[j] * g(p[j].x, p[j].y, p[i].x, p[i].y))) %= mod;
    }
    cout << (dp[c] + mod) % mod << '\n';

    return 0;
}