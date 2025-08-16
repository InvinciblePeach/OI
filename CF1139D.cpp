#include <bits/stdc++.h>
#define int long long

using namespace std;

constexpr int MAXN = 1e6 + 10, mod = 1e9 + 7;
int m, ans = 1, mu[MAXN], inv[MAXN];
bitset<MAXN> p;
vector<int> prime;

void init() {
    mu[1] = inv[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
        if (!p[i]) {
            prime.emplace_back(i);
            mu[i] = -1;
        }

        for (auto j : prime) {
            if (i * j >= MAXN) break;
            p[i * j] = 1;
            if (i % j == 0) {
                mu[i * j] = 0;
                break;
            }
            mu[i * j] = -mu[i];
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> m;
    init();
    for (int d = 2; d <= m; d++)
        (ans += mod - mu[d] * (m / d) % mod * inv[m - m / d] % mod) %= mod;
    cout << (ans + mod) % mod << '\n';
    return 0;
}