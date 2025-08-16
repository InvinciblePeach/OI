#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 2e5 + 10, V = 1e6 + 10, mod = 998244353;
int n, ans, a[MAXN], c[V], mu[V], inv[V];
bitset<V> p;
vector<int> prime;

void init() {
    inv[1] = mu[1] = 1;
    for (int i = 2; i < V; i++) {
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
        if (!p[i]) {
            prime.emplace_back(i);
            mu[i] = -1;
        }

        for (auto j : prime) {
            if (i * j >= V) break;
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

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    init();

    for (int i = 1; i <= n; i++)
        (c[a[i]] += a[i]) %= mod;
    for (auto j : prime)
        for (int i = (V - 1) / j; i; i--)
            (c[i] += c[i * j]) %= mod;
    for (int i = 1; i < V; i++) (c[i] *= c[i]) %= mod;

    for (int d = 1; d < V; d++)
        for (int t = 1; d * t < V; t++)
            ans += mu[t] * inv[d] % mod * c[d * t] % mod;
            // cerr << t << '\n';
    for (int i = 1; i <= n; i++) (ans -= a[i]) %= mod;
    cout << (ans * inv[2] % mod + mod) % mod << '\n';

    return 0;
}