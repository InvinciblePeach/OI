#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1010, MAXM = 2010;
int n, m, cnt = -1;
bitset<MAXN> a[MAXM];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        static string w;
        static char c;
        cin >> w >> c;
        reverse(w.begin(), w.end());
        a[i] = bitset<MAXN>(c + w + '0');
    }

    for (int i = 1; i <= n; i++) {
        int nw = i;
        while (nw <= m && !a[nw][i]) nw++;
        if (nw > m) return cout << "Cannot Determine\n", 0;
        cnt = max(cnt, nw);
        swap(a[i], a[nw]);
        for (int j = 1; j <= m; j++)
            if ((i ^ j) && a[j][i]) a[j] ^= a[i];
    }
    cout << cnt << '\n' ;
    for (int i = 1; i <= n; i++) cout << (a[i][n + 1] ? "?y7M#\n" : "Earth\n");

    return 0;
}