#include <bits/stdc++.h>

using namespace std;

constexpr uint MAXN = 2e7 + 10;
uint T, N, K, n, ans, f[MAXN], F[MAXN];
bitset<MAXN> p;
vector<uint> prime;

constexpr uint qpow(uint a, uint b) {
    uint res = 1;
    while (b) {
        if (b & 1) res *= a;
        a *= a, b >>= 1;
    }
    return res;
}

void init() {
    f[1] = F[1] = 1;
    for (uint i = 2; i <= N; i++) {
        if (!p[i]) {
            prime.emplace_back(i);
            f[i] = i - 1;
            F[i] = qpow(i, K);
        }

        for (auto j : prime) {
            if (i * j > N) break;
            p[i * j] = 1;
            F[i * j] = F[i] * F[j];
            if (i % j == 0) {
                if (i / j % j) f[i * j] = f[i / j] * -j;
                break;
            }
            f[i * j] = f[i] * (j - 1);
        }
    }
    for (uint i = 2; i <= N; i++) f[i] = f[i - 1] + f[i] * F[i];
    for (uint i = 2; i <= N; i++) F[i] += F[i - 1];
    for (uint i = 2; i <= N; i++) F[i] += F[i - 1];
}

uint calc(const uint &x) { return F[x << 1] - (F[x] << 1); }

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T >> N >> K;
    N <<= 1;
    init();
    while (T-- > 0) {
        cin >> n;
        ans = 0;
        for (uint l = 1, r; l <= n; l = r + 1) {
            r = n / (n / l);
            ans += calc(n / l) * (f[r] - f[l - 1]);
        }
        cout << ans << '\n';
    }
    return 0;
}