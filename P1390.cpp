#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 2e6 + 10;
int n, ans, phi[MAXN];
vector<int> prime;
bitset<MAXN> p;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!p[i]) {
            prime.emplace_back(i);
            phi[i] = i - 1;
        }

        for (auto j : prime) {
            if (i * j > n) break;
            p[i * j] = 1;

            if (!(i % j)) {
                phi[i * j] = phi[i] * j;
                break;
            }

            phi[i * j] = phi[i] * phi[j];
        }
    }

    for (int i = 1; i <= n; i++) phi[i] += phi[i - 1];

    for (int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans += (phi[r] - phi[l - 1]) * (n / l) * (n / l);
    }
    ans -= n * (n + 1) / 2;
    ans /= 2;
    cout << ans << '\n';

    return 0;
}