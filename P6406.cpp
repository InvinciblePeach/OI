#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 5e5 + 10, mod = 1e9;
int n, ans, a[MAXN], s1[MAXN], s2[MAXN], s3[MAXN], t1[MAXN], t2[MAXN], t3[MAXN];

void solve(int l, int r, int d = 0) {
    if (l == r) return (ans += a[l] * a[l] % mod) %= mod, void();

    int mid, lmn, lmx, rmn, rmx;
    mid = (l + r) >> 1, lmx = rmx = INT_MIN, lmn = rmn = INT_MAX;
    s1[mid] = s2[mid] = s3[mid] = t1[mid] = t2[mid] = t3[mid] = 0;

    for (int i = mid + 1; i <= r; i++) {
        rmn = min(rmn, a[i]), rmx = max(rmx, a[i]);
        s1[i] = (s1[i - 1] + rmn * (i - mid) % mod) % mod, t1[i] = (t1[i - 1] + rmn) % mod;
        s2[i] = (s2[i - 1] + rmx * (i - mid) % mod) % mod, t2[i] = (t2[i - 1] + rmx) % mod;
        s3[i] = (s3[i - 1] + rmn * rmx % mod * (i - mid) % mod) % mod, t3[i] = (t3[i - 1] + rmn * rmx % mod) % mod;
    }
    for (int i = mid, j = mid, k = mid; i >= l; i--) {
        lmn = min(lmn, a[i]), lmx = max(lmx, a[i]);
        while (j < r && a[j + 1] > lmn)
            j++;
        while (k < r && a[k + 1] < lmx)
            k++;
        int w1 = min(j, k), w2 = max(j, k);
        if (w1 > mid) (ans += lmn * lmx % mod * ((mid + 1 - i + 1 + w1 - i + 1) * (w1 - mid) / 2 % mod) % mod) %= mod;
        if (j > w1) (ans += lmn * ((s2[j] - s2[w1]) % mod + (mid - i + 1) * (t2[j] - t2[w1]) % mod) % mod) %= mod;
        if (k > w1) (ans += lmx * ((s1[k] - s1[w1]) % mod + (mid - i + 1) * (t1[k] - t1[w1]) % mod) % mod) %= mod;
        (ans += ((s3[r] - s3[w2]) % mod + (mid - i + 1) * (t3[r] - t3[w2]) % mod) % mod) %= mod;
    }
    solve(l, mid, d + 1), solve(mid + 1, r, d + 1);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    solve(1, n);
    cout << ans << '\n';

    return 0;
}