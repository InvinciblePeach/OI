#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 1e6 + 10, mod = 104857601;
int n, ans = 1, frac = 1, phi[MAXN];
bitset<MAXN> p;
vector<int> prime;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = ll(res) * a % mod;
        a = ll(a) * a % mod, b >>= 1;
    }
    return res;
}

int inv(int a) { return qpow(a, mod - 2); }

void init() {
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        frac = ll(frac) * i % mod;
        if (!p[i]) {
            prime.emplace_back(i);
            phi[i] = i - 1;
        }

        for (auto j : prime) {
            if (i * j > n) break;
            p[i * j] = 1;
            if (i % j == 0) {
                phi[i * j] = phi[i] * j;
                break;
            }
            phi[i * j] = phi[i] * (j - 1);
        }
    }
    for (int i = 1; i <= n; i++)
        phi[i] = (phi[i] << 1) + phi[i - 1] % (mod - 1);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    init();
    for (int d = 2; d <= n; d++)
        ans = ll(ans) * qpow(d, phi[n / d] - 1) % mod;
    cout << ll(qpow(frac, n << 1)) * inv(ll(ans) * ans % mod) % mod << '\n';

    return 0;
}