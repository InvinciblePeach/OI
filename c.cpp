#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128 = __int128_t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if (!(cin >> n >> k)) return 0;
    vector<int64> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a.begin(), a.end());

    // 前缀和，pref[i] = a[0] + ... + a[i-1]
    vector<int64> pref(n + 1, 0);
    for (int i = 1; i <= n; ++i) pref[i] = pref[i - 1] + a[i - 1];

    auto good = [&](int64 s) -> bool {
        // m = 个数 a_i <= s
        int m = upper_bound(a.begin(), a.end(), s) - a.begin();
        // need = m*(s+1) - sum_{i=1..m} a_i
        i128 need = (i128)m * (s + 1) - (i128)pref[m];
        i128 cap = (i128)k * s;
        return need <= cap;
    };

    // 指数拓展上界
    int64 low = 0, high = 1;
    const int64 LIM = (int64)4e18; // 防止溢出
    while (high < LIM && good(high)) {
        if (high > (LIM >> 1)) { // 乘2会溢出，就停在这里
            high = LIM;
            break;
        }
        high <<= 1;
    }
    if (high == LIM && good(high)) {
        cout << high << '\n';
        return 0;
    }

    while (low < high) {
        int64 mid = low + (high - low + 1) / 2;
        if (good(mid))
            low = mid;
        else
            high = mid - 1;
    }
    cout << low << '\n';
    return 0;
}
