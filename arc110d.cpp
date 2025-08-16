#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 2010, mod = 1e9 + 7;
int n, m, a[MAXN], sum;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}

int frac(int a) {
    int res = 1;
    for (int i = 1; i <= a; i++) (res *= i) %= mod;
    return res;
}

int inv(int a) { return qpow(a, mod - 2); }

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i], sum += a[i];
    
    int ans = 1;
    for (int i = m + n; i > m - sum; i--)
        (ans *= i) %= mod;
    (ans *= inv(frac(sum + n))) %= mod;
    cout << ans << '\n';
    return 0;
}