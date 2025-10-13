#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 5e7 + 10, mod = 998244353;
int n, c, ans, f[MAXN], v[MAXN], inv[110];
bitset<MAXN> p;
vector<int> prime;

signed main() {
    freopen("array.in", "r", stdin);
    freopen("array.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> c;

    inv[1] = 1;
    for (int i = 2; i <= 100; i++) inv[i] = ll(mod - mod / i) * inv[mod % i] % mod;

    v[1] = 0, f[1] = 1;
    for (int i = 2; i <= c; i++) {
        if (!p[i]) {
            prime.emplace_back(i);
            f[i] = n, v[i] = 1;
        }

        for (auto j : prime) {
            if (i * j > c) break;
            p[i * j] = 1;
            if (i % j == 0) {
                v[i * j] = v[i] + 1;
                f[i * j] = (ll)f[i] * (v[i] + n) % mod * inv[v[i] + 1] % mod;
                break;
            }
            f[i * j] = (ll)f[i] * f[j] % mod, v[i * j] = 1;
        }
    }
    for (int i = 1; i <= c; i++) ans = ((ll)ans + f[i]) % mod;
    cout << ans << '\n';

    return 0;
}