#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;
int T, n, a[MAXN], b[MAXN], pre[MAXN], suf[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T-- > 0) {
        cin >> n;
        pre[1] = 1, suf[n] = n;
        for (int i = 2; i <= n; i++)
            cin >> a[i], pre[i] = (a[i] < a[pre[i - 1]] ? i : pre[i - 1]);
        for (int i = n - 1; i; i--)
            suf[i] = (a[i] > a[suf[i + 1]] ? i : suf[i + 1]);
        for (int i = 1; i <= n; i++) cin >> b[i];
        auto calc = [=]() -> int {
            int l = 1, r = 1, res = 0;
            for (int i = 1; i <= n; i++) {
                if (a[l] > b[r])
                    res++, l++;
                else
                    r++;
            }
            return res;
        };
        int l = calc(), r = n + 1;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            swap(a[pre[mid - 1]], a[suf[mid]]);
            if (calc() >= mid)
                l = mid;
            else
                r = mid;
            swap(a[pre[mid - 1]], a[suf[mid]]);
        }
        cout << l << '\n';
    }

    return 0;
}