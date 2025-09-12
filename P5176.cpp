#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 2e7 + 10, mod = 1e9 + 7;
int T, n, m, p, f[MAXN];
bitset<MAXN> vis;
vector<int> prime;

void init() {
    f[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        if (!vis[i]) {
            prime.emplace_back(i);
            f[i] = (i * i % mod + mod - 1) % mod;
        }

        for (auto j : prime) {
            if (i * j >= MAXN) break;
            vis[i * j] = 1;
            if (!(i % j)) {
                f[i * j] = f[i] * j % mod * j % mod;
                break;
            }
            f[i * j] = f[i] * f[j] % mod;
        }
    }
    for (int i = 1; i < MAXN; i++) (f[i] += f[i - 1]) %= mod;
}

int calc(int x, int y) {
    int res = 0;

    for (int l = 1, r; l <= min(x, y); l = r + 1) {
        r = min(x / (x / l), y / (y / l));
        (res += (x / l) * (y / l) % mod * (f[r] - f[l - 1]) % mod) %= mod;
    }
    return (res + mod) % mod;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    init();
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m >> p;
        cout << (p * calc(n, m) % mod + n * calc(m, p) % mod + m * calc(n, p) % mod) % mod << '\n';
    }

    return 0;
}