#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 5010, MAXV = 1e6 + 10, MAXM = 1010, mod = 998244353;
int n, a[MAXN], b[MAXN], pre[MAXM][MAXM], fac[MAXV][3];
bitset<MAXV> p;
vector<int> prime;

void init() {
    fac[1][0] = fac[1][1] = fac[1][2] = 1;
    for (int i = 2; i < MAXV; i++) {
        if (!p[i]) {
            fac[i][0] = fac[i][1] = 1;
            fac[i][2] = i;
            prime.emplace_back(i);
        }
        for (auto j : prime) {
            int k = i * j;
            if (k >= MAXV) break;
            p[k] = 1;
            fac[k][0] = fac[i][0] * j;
            fac[k][1] = fac[i][1];
            fac[k][2] = fac[i][2];
            sort(fac[k], fac[k] + 3);
            if (!(i % j)) break;
        }
    }
    for (int i = 0; i < MAXM; i++) pre[i][0] = pre[0][i] = i;
    for (int i = 1; i < MAXM; i++)
        for (int j = 1; j <= i; j++) pre[i][j] = pre[j][i] = pre[j][i % j];
}

int gcd(int a, int b) {
    int res = 1;
    for (auto i : fac[a]) {
        int tmp = i >= MAXM ? (b % i ? 1 : i) : pre[i][b % i];
        b /= tmp, res *= tmp;
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    init();
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= n; i++) {
        ll sum = 0, tmp = i;
        for (int j = 1; j <= n; j++, (tmp *= i) %= mod) (sum += tmp * gcd(a[i], b[j])) %= mod;
        cout << sum << '\n';
    }

    return 0;
}