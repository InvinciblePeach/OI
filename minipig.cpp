#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e6 + 10;
int N, m, q, T[4][MAXN];

signed main() {
    // freopen("minipig.in", "r", stdin);
    // freopen("minipig.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> m >> q;
    for (int i = 1, t, p, d, v; i <= m; i++) {
        cin >> t >> p >> d >> v;
        int r;
        if (d) r = min(t + (N - p) / v, N << 1);
        else r = min(t + (p - 1) / v, N << 1);
        
        if (v & 1) {
            if ((p + t) & 1) {
                T[1][t]++, T[1][r + 1]--;
                T[2][t]++, T[2][r + 1]--;
            } else {
                T[0][t]++, T[0][r + 1]--;
                T[3][t]++, T[3][r + 1]--;
            }
        } else {
            if (p & 1) {
                T[0][t]++, T[0][r + 1]--;
                T[2][t]++, T[2][r + 1]--;
            } else {
                T[1][t]++, T[1][r + 1]--;
                T[3][t]++, T[3][r + 1]--;
            }
        }
    }

    for (int i = 1; i < MAXN; i++)
        T[0][i] += T[0][i - 1], T[1][i] += T[1][i - 1],
            T[2][i] += T[2][i - 1], T[3][i] += T[3][i - 1];

    while (q --> 0) {
        int t;
        cin >> t;
        if (t & 1)
            cout << T[0][t] << ' ' << T[1][t] << '\n';
        else
            cout << T[2][t] << ' ' << T[3][t] << '\n';
    }
    return 0;
}