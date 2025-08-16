#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 1e6 + 10, mod = 998244353;
int n, a[MAXN][10], b[MAXN], s[MAXN], cnt, ans;
vector<int> pos[MAXN];

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

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 6; j++) {
            cin >> a[i][j];
            s[++cnt] = a[i][j];
        }
    }
    sort(s + 1, s + 1 + cnt);
    cnt = unique(s + 1, s + 1 + cnt) - s - 1;

    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= 6; j++)
            pos[lower_bound(s + 1, s + 1 + cnt, a[i][j]) - s].emplace_back(i);

    int prod = 1, zero = n;
    for (int i = 1; i < cnt; i++) {
        for (auto j : pos[i]) {
            if (!b[j]) zero--;
            else (prod *= inv(b[j])) %= mod;
            (prod *= ++b[j]) %= mod;
        }
        (ans -= (zero ? 0 : prod) * (s[i + 1] - s[i]) % mod) %= mod;
    }
    (ans *= inv(qpow(6, n))) %= mod;
    (ans += s[cnt]) %= mod;
    cout << (ans + mod) % mod << '\n';

    return 0;
}