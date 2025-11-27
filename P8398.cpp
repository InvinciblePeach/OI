#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 1e6 + 10;
int n, c, ans, cnt[MAXN << 1], sum[MAXN << 1];

int calc(int l, int r) { return sum[r] - sum[l - 1]; }
int C2(int x) { return x > 1 ? x * (x - 1) >> 1 : 0; }
int C3(int x) { return x > 2 ? x * (x - 1) * (x - 2) / 6 : 0; }

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> c;
    for (int i = 1, x; i <= n; i++) cin >> x, cnt[x]++, cnt[x + c]++;
    sum[0] = cnt[0];
    for (int i = 1; i <= (c << 1); i++) sum[i] = sum[i - 1] + cnt[i];
    int tmp = c >> 1;
    ans = C3(n);
    for (int i = c; i < (c << 1); i++) {
        ans -= C2(calc(i - tmp, i - 1)) * cnt[i];
        ans -= C2(cnt[i]) * calc(i - tmp + !(c & 1), i - 1);
        ans -= C3(cnt[i]);
    }
    cout << ans << '\n';

    return 0;
}