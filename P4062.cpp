#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 5e5 + 10;
int n, typ, ans, a[MAXN], sum[MAXN << 1], add[MAXN << 1];
vector<int> pos[MAXN];

void modify(int l, int r, int val) { add[l + MAXN] += val, add[r + MAXN + 1] -= val; }

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> typ;
    modify(1, 1, 1);
    for (int i = 0; i < n; i++) pos[i].emplace_back(0);
    for (int i = 1; i <= n; i++) pos[cin >> a[i], a[i]].emplace_back(i);
    for (int i = 0; i < n; i++) pos[i].emplace_back(n + 1);
    for (int i = 0; i < n; i++) {
        int d = 0, t = 0, mn = 0;
        auto &pos = ::pos[i];
        for (int j = 1; j < pos.size(); j++) {
            int r = sum[j - 1] - 1, l = r - (pos[j] - pos[j - 1]) + 2;
            if (l <= r && pos[j - 1]) {
                int lim = max(mn, l);
                for (int k = r; k >= lim; k--) {
                    ans += (t -= d);
                    d -= add[k + MAXN + 1];
                }
            }
            if (j == pos.size() - 1) break;
            modify(l + 1, r + 1, 1);
            d += add[l + MAXN + 1];
            ans += (t += d);
            sum[j] = l + 1;
            modify(sum[j] + 1, sum[j] + 1, 1);
            mn = min(mn, l);
        }
        for (int j = 1; j < pos.size() - 1; j++) modify(sum[j], sum[j - 1], -1), modify(sum[j] + 1, sum[j] + 1, -1);
    }
    cout << ans << '\n';

    return 0;
}