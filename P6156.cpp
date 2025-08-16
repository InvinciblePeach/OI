#include <bits/stdc++.h>
#define int long long

using namespace std;

constexpr int MAXN = 1e7 + 10, mod = 998244353;
int n, k, ans, f[MAXN], F[MAXN];
bitset<MAXN> p;
vector<int> prime;

constexpr int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        (a *= a) %= mod, b >>= 1;
    }
    return res;
}

void init() {
    f[1] = F[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        if (!p[i]) {
            prime.emplace_back(i);
            f[i] = i - 1;
            F[i] = qpow(i, k);
        }

        for (auto j : prime) {
            if (i * j >= MAXN) break;
            p[i * j] = 1;
            F[i * j] = F[i] * F[j] % mod;
            if (i % j == 0) {
                if (i / j % j)
                    f[i * j] = f[i / j] * (mod - j) % mod;
                break;
            }
            f[i * j] = f[i] * (j - 1) % mod;
        }
    }
    for (int i = 2; i < MAXN; i++) f[i] = (f[i - 1] + f[i] * F[i]) % mod;
    for (int i = 2; i < MAXN; i++) (F[i] += F[i - 1]) %= mod;
    for (int i = 2; i < MAXN; i++) (F[i] += F[i - 1]) %= mod;
}

int calc(const int &x) { return (F[x << 1] - (F[x] * 2)) % mod; }

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> k;
    init();
    for (int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        (ans += calc(n / l) * (f[r] - f[l - 1]) % mod) %= mod;
    }
    cout << (ans + mod) % mod << '\n';
    return 0;
}