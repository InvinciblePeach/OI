#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 5e5 + 10;
int T, n, a[MAXN], b[MAXN], m1[MAXN], m2[MAXN], m3[MAXN], ma[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T-- > 0) {
        cin >> n;
        m1[0] = m2[0] = m3[0] = 0x3f3f3f3f;
        m3[n + 1] = -0x3f3f3f3f;
        ma[n + 1] = -0x3f3f3f3f;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            m1[i] = m1[i - 1];
            m2[i] = m2[i - 1];
            if (m1[i] > a[i]) {
                m2[i] = m1[i];
                m1[i] = a[i];
            } else if (m2[i] > a[i])
                m2[i] = a[i];
        }
        for (int i = 1; i <= n; i++)
            cin >> b[i];
        for (int i = n; i >= 1; i--)
            ma[i] = max(ma[i + 1], a[i]);
        for (int i = 1; i <= n; i++)
            m3[i] = min(m3[i - 1], b[i]);
        for (int ans = n; ans >= 0; ans--)
            if (max(m1[ans], min(m2[ans], ma[ans + 1])) > m3[n - ans + 1]) {
                cout << ans << '\n';
                break;
            }
    }

    return 0;
}