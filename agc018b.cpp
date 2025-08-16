#include <bits/stdc++.h>

using namespace std;

const int MAXN = 310;
int N, m, ans = INT_MAX, a[MAXN][MAXN], ptr[MAXN], cnt[MAXN];
bitset<MAXN> del;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> m;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
        ptr[i] = 1;
        cnt[a[i][1]]++;
    }
    
    for (int i = 1; i <= m; i++) {
        int mx = 0, id;
        for (int j = 1; j <= m; j++)
            if (cnt[j] > mx) mx = cnt[j], id = j;
        del[id] = 1, cnt[id] = 0;
        memset(cnt, 0, sizeof(cnt));
        ans = min(ans, mx);
        for (int k = 1; k <= N; k++) {
            while (del[a[k][ptr[k]]]) ptr[k]++;
            cnt[a[k][ptr[k]]]++;
        }
    }
    cout << ans << '\n';
    return 0;
}