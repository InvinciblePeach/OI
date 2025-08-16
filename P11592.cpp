#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 110;
int T, n, sum, a[MAXN], b[MAXN], tmpa[MAXN], tmpb[MAXN], pos[MAXN], s[MAXN], I[MAXN], nw[MAXN];
bitset<MAXN> vis;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T --> 0) {
        cin >> n;
        sum = 0;
        for (int i = 1; i <= n; i++) {
            cin >> s[i];
            sum += (s[i] %= n);
            a[i] = i - 1, pos[b[i] = n - i] = i, nw[i] = n - 1;
        }
        if (sum % n) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";

        for (int i = 1; i < n; i++) {
            if (s[i] == n - 1) continue;
            nw[n] = (nw[n] + nw[i] - s[i] + n) % n, nw[i] = s[i];
            vis.reset();
            vis[I[1] = i] = 1, I[2] = n;

            int q = 2;
            while (!vis[I[q]]) {
                vis[I[q]] = 1;
                I[q + 1] = pos[(nw[I[q]] - a[I[q - 1]] + n) % n];
                q++;
            }

            memcpy(tmpa, a, sizeof(a)), memcpy(tmpb, b, sizeof(b));
            a[I[1]] = a[I[q - 1]], b[I[1]] = b[I[1] + I[2] - I[q]];
            for (int j = 2; j < q; j++)
                a[I[j]] = tmpa[I[j - 1]], b[I[j]] = tmpb[I[j + 1]];
            for (int j = 1; j <= n; j++)
                pos[b[j]] = j;
        }
        for (int i = n - 1; ~i; i--)
            cout << (s[pos[i]] ? s[pos[i]] : n) << ' ';
        cout << '\n';
    }

    return 0;
}