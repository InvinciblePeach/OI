#include <bits/stdc++.h>
#define rep(x, y, z) for (int x = (y); x <= z; x++)
#define per(x, y, z) for (int x = (y); x >= z; x--)

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 5e5 + 10;
int n, m, sum, cnt[MAXN];

int calc(int x) {
    int res = 0;
    while (x) res++, x /= 10;
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    rep(i, 1, n) {
        int a;
        cin >> a;
        if (!cnt[a]) {
            if (!sum)
                sum += calc(a);
            else
                sum += calc(a) + 1;
        }
        cnt[a] = sum;
    }
    rep(i, 1, m) cout << cnt[i] << " \n"[i == m];

    return 0;
}