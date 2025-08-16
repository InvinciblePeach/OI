#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 1e6 + 10, mod = 1e9;
int n, k, a[MAXN], sum[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> k;
    a[0] = sum[0] = 1;
    for (int i = 1; i < k; i++) a[i] = 1, sum[i] = (sum[i - 1] + a[i]) % mod;
    for (int i = k; i <= n; i++) {
        a[i] = (sum[i - 1] - sum[i - k - 1]) % mod;
        sum[i] = (sum[i - 1] + a[i]) % mod;
    }
    cout << (a[n] + mod) % mod << '\n';

    return 0;
}